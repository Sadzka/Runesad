#pragma once

#ifndef SADZA_GAME_HPP
#define SADZA_GAME_HPP

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
//#include "Input/InputManager.hpp"
#include <windows.h>
#include "SharedContext.hpp"
class Game {

public:
    Game();

    ~Game();

    Game(const Game &) = delete;

    Game &operator=(const Game &) = delete;

    void update();

    void render();

    void lateUpdate();

    void restartClock();

    Window *getWindow();

private:

    sf::Clock clock;
    sf::Time deltaTime;

//    Client              client;
    float fps_clock;
    int frames;

    void FPSLimit();
};

#endif //SADZA_GAME_HPP
