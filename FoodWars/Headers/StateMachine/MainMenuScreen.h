#pragma once

#ifndef PROJECT_SWA_MAINMENUSCREEN_H
#define PROJECT_SWA_MAINMENUSCREEN_H

#include "IScreen.h"
#include "ScreenStateManager.h"
#include "GameScreen.h"
#include "../../Headers/StateMachine/OtherMenuScreen.h"
#include "../../../TonicEngine/Headers/Events/MouseEvent.h"
#include "../../../TonicEngine/Headers/Input/IObserver.h"
#include "../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/TextButton.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"

class MainMenuScreen : public IScreen, public IObserver<KeyEvent> {
private:
    std::shared_ptr<VisualFacade> visualFacade;
    std::shared_ptr<AudioFacade> audioFacade;
    Renderlist _renderList;
    std::vector<IShape*> _buttons;
public:
    MainMenuScreen(std::shared_ptr<ScreenStateManager> context);
    ~MainMenuScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;
};

#endif //PROJECT_SWA_MAINMENUSCREEN_H
