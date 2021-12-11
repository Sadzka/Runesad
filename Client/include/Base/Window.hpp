//
// Created by Sadza on 12.06.2021.
//

#pragma once

#ifndef SADZA_WINDOW_HPP
#define SADZA_WINDOW_HPP


#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <string>
//#include "Input/InputManager.hpp"
#include "Variables.hpp"

class Window {
    sf::RenderWindow window;
    bool closed;
    std::string title;
    bool focused;
    sf::Event event;
//    InputManager            inpMgr;

    void setup(const std::string &title, const sf::Vector2u &size);

    void create(const sf::Vector2u &size);

    void destroy();

public:
    Window();

    Window(const std::string &title, const sf::Vector2u &size);

    void init(const std::string &title, const sf::Vector2u &size);

    Window(const Window &) = delete;

    ~Window();

    void update();

    void toggleFullscreen(/*Binding * bind*/);

    void close(/*Binding * bind*/);

    sf::Vector2u getWindowSize();

    sf::RenderWindow *getRenderWindow();

    bool isClosed();

    bool isFocused();

    void beginDraw();

    void endDraw();

    void draw(sf::Drawable &drawable);

//    InputManager * getInputManager();
};

#endif //SADZA_WINDOW_HPP
