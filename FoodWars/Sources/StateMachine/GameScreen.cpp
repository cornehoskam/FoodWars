#include "../../Headers/GameECS/Components/MoveComponent.h"
#include "../../Headers/GameECS/Systems/CollisionSystem.h"
#include "../../Headers/GameECS/Systems/JumpSystem.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../Headers/StateMachine/PauseScreen.h"
#include "../../Headers/GameECS/Systems/AnimationSystem.h"
#include "../../Headers/GameECS/Components/AnimationComponent.h"
#include "../../Headers/GameECS/Systems/DamageableSystem.h"
#include "../../Headers/StateMachine/DrawTransitionScreen.h"
#include "../../Headers/StateMachine/WinTransitionScreen.h"
#include "../../Headers/StateMachine/LoseTransitionScreen.h"

GameScreen::GameScreen(const std::shared_ptr<ScreenStateManager>& context, EntityManager entityManager) : IScreen(context), _entityManager(std::make_shared<EntityManager>(entityManager))
{
    _audioFacade = _context->getFacade<AudioFacade>();
    _visualFacade = _context->getFacade<VisualFacade>();
    _inputFacade->getKeyEventObservable()->registerKeyEventObserver(this);
    _animationManager = new AnimationManager{};
    CollisionSystem* collisionSystem = new CollisionSystem{ _entityManager };
    _systems.push_back(new JumpSystem { _entityManager, _inputFacade, audioFacade, *collisionSystem } );
    _systems.push_back(new MoveSystem { _entityManager, _inputFacade, *collisionSystem });
    _systems.push_back(new GravitySystem { _entityManager, *collisionSystem });
    _systems.push_back(new AnimationSystem(_entityManager, _animationManager));
    TurnSystem* turnSystem = new TurnSystem {_entityManager};
    _systems.push_back(turnSystem);
    _shootingSystem = new ShootingSystem(_entityManager, audioFacade, visualFacade, _inputFacade);
    _systems.push_back(_shootingSystem);
    _systems.push_back(new DamageableSystem { _entityManager, *collisionSystem});
    _systems.push_back(collisionSystem);

    drawSystem = new DrawSystem {_entityManager, visualFacade, _inputFacade};
    _systems.push_back(drawSystem);

    int count = 0;
    for (auto const& t : _entityManager->getAllEntitiesWithComponent<TurnComponent>())
    {
        if (count == 0) playerOne = t.first;
        else playerTwo = t.first;
        count++;
    }
}

void GameScreen::update(std::shared_ptr<KeyEvent> event){
    if (event->getKeyEventType() == KeyEventType::Down) {
        if(event->getKey() == KEY::KEY_ESCAPE)
            _context->setActiveScreen<PauseScreen>();

        //Adjusting gamespeed
        if(event->getKey() == KEY::KEY_PAGEUP) {
            _context->setTimeModifier(2.50);
        }
        if(event->getKey() == KEY::KEY_PAGEDOWN) {
            _context->setTimeModifier(0.40);
        }
        if(event->getKey() == KEY::KEY_HOME) {
            _context->setTimeModifier(1);
        }

        if (event->getKey() == KEY::KEY_G){
            _shootingSystem->toggleShooting();
        }
        //Toggle Framerate
        if(event->getKey() == KEY::KEY_F){
            drawSystem->toggleFpsCounter();
        }
    }
}

GameScreen::~GameScreen() {
    for (auto const &iterator : _systems) {
        delete iterator;
    }
    delete _animationManager;
};

void GameScreen::update(double deltaTime) {
    std::map<int, std::shared_ptr<TurnComponent>> _entitiesWithTurnComponent = _entityManager->getAllEntitiesWithComponent<TurnComponent>();
    if(_entitiesWithTurnComponent.size() == 1)
    {
        //set score
        if (_entityManager->exists(playerOne)) _context->setActiveScreen<WinTransitionScreen>();
        else _context->setActiveScreen<LoseTransitionScreen>();

    } else if(_entitiesWithTurnComponent.empty()) {
        //set score
        _context->setActiveScreen<DrawTransitionScreen>();
    }
    _audioFacade->playMusic("nature");
    _inputFacade->pollEvents();
    for(auto const &iterator : _systems){
        iterator->update(deltaTime * _context->getTimeModifier());
    }
}