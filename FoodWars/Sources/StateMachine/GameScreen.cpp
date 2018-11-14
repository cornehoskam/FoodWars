#include <utility>

#include <utility>
#include "../../Headers/StateMachine/GameScreen.h"
#include "../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../../Headers/GameECS/Components/TurnComponent.h"
#include "../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../Headers/GameECS/Components/GravityComponent.h"
#include "../../Headers/GameECS/Components/MoveComponent.h"
#include "../../Headers/GameECS/Systems/CollisionSystem.h"
#include "../../Headers/GameECS/Systems/JumpSystem.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../Headers/StateMachine/PauseScreen.h"

GameScreen::GameScreen(const std::shared_ptr<ScreenStateManager>& context, EntityManager entityManager) : IScreen(context),
                                                                                        _entityManager(std::make_shared<EntityManager>(entityManager))
{
    _inputFacade->getKeyEventObservable()->registerKeyEventObserver(this);
    CollisionSystem* collisionSystem = new CollisionSystem{ _entityManager };
    _systems.push_back(new JumpSystem { _entityManager, _inputFacade, *collisionSystem } );
    _systems.push_back(new MoveSystem { _entityManager, _inputFacade, *collisionSystem });
    _systems.push_back(collisionSystem);
    _systems.push_back(new GravitySystem { _entityManager, *collisionSystem });
    _systems.push_back(new DrawSystem {_entityManager, visualFacade});

    TurnSystem* turnSystem = new TurnSystem {_entityManager};
    _systems.push_back(turnSystem);
}

void GameScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE && event->getKeyEventType() == KeyEventType::Down)
        _context->setActiveScreen<PauseScreen>();

    //Adjusting gamespeed
    if(event->getKey() == KEY::KEY_PAGEUP && event->getKeyEventType() == KeyEventType::Down)
        _context->setTimeModifier(2.50);
    if(event->getKey() == KEY::KEY_PAGEDOWN && event->getKeyEventType() == KeyEventType::Down)
        _context->setTimeModifier(0.40);
    if(event->getKey() == KEY::KEY_HOME && event->getKeyEventType() == KeyEventType::Down)
        _context->setTimeModifier(1);
}

GameScreen::~GameScreen() {
    for (auto const &iterator : _systems) {
        delete iterator;
    }
};

void GameScreen::update(double deltaTime) {
    audioFacade->playMusic("wildwest");
    _inputFacade->pollEvents();
    for(auto const &iterator : _systems){
        iterator->update(deltaTime * _context->getTimeModifier());
    }
}