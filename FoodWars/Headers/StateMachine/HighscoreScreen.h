#ifndef PROJECT_SWA_HIGHSCORESCREEN_H
#define PROJECT_SWA_HIGHSCORESCREEN_H

#include "IScreen.h"
#include "../../../TonicEngine/Headers/Storage/StorageFacade.h"

class HighscoreScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit HighscoreScreen(ScreenStateManager& context);
    ~HighscoreScreen();
    void update(double deltaTime) override;
    void update(const KeyEvent& event) override;

    void refreshScoreText();
private:

    void placeShape(int xpos, int ypos, std::string text, int width, int height, Colour colour);
    void alterIndex(int dir);

    int _currentIndex;
    std::vector<std::string> _scoreText;
    MouseEventObservable* _mouseEventObservable;
    std::vector<ShapeText*> _visualScores;
};


#endif //PROJECT_SWA_HIGHSCORESCREEN_H
