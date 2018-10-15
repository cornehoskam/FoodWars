#ifndef PROJECT_SWA_SCREENSTATE_H
#define PROJECT_SWA_SCREENSTATE_H

#include "memory"
#include <vector>
#include <iostream>
#include <typeinfo>
#include <map>
#include "../../../TonicEngine/Facades/IFacade.h"
#include "../../../TonicEngine/Headers/Visual/VisualFacade.h"
#include "IScreen.h"

class ScreenStateManager {
private:
    std::shared_ptr<IScreen> _currentState;
    std::map<std::string, std::shared_ptr<IScreen>> _screenStates;
    std::map<std::string, std::shared_ptr<IFacade>> _facades;
public:
    ScreenStateManager();
    std::shared_ptr<IScreen> getCurrentState();

    template<typename Screen, typename std::enable_if<std::is_base_of<IScreen, Screen>::value>::type* = nullptr>
    void addOrSetScreenState(Screen* screen){
        _screenStates[typeid(Screen).name()] = std::shared_ptr<IScreen>(screen);
    }

    template<typename Screen, typename std::enable_if<std::is_base_of<IScreen, Screen>::value>::type* = nullptr>
    void setActiveScreen() {
        std::string screenName = typeid(Screen).name();
        if(_screenStates.count(screenName) > 0){
            _currentState = _screenStates[screenName];
        }
    }

    /*template<typename Screen, typename std::enable_if<std::is_base_of<IScreen, Screen>::value>::type* = nullptr>
    void setActiveScreen(std::shared_ptr<Screen> s){
        _currentState = s;
    }*/

    template<typename Facade, typename std::enable_if<std::is_base_of<IFacade, Facade>::value>::type* = nullptr>
    void addFacade(Facade* facade) {
        _facades[typeid(Facade).name()] = std::shared_ptr<IFacade>(facade);
    }

    template<typename Facade>
    std::shared_ptr<Facade> getFacade() {
        std::string facadeName = typeid(Facade).name();
        if(_facades.count(facadeName) > 0){
            return std::dynamic_pointer_cast<Facade>(_facades[facadeName]);
        }
        return nullptr;
    }
};

#endif //PROJECT_SWA_SCREENSTATE_H