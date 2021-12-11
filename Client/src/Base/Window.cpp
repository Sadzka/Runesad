//
// Created by Sadza on 12.06.2021.
//

#include "Base/Window.hpp"
#include "Base/SharedContext.hpp"

Window::Window() {
    setup("Window", sf::Vector2u(800, 600));
}

Window::Window(const std::string &title, const sf::Vector2u &size) {
    setup(title, size);
}

void Window::init(const std::string &title, const sf::Vector2u &size) {
    setup(title, size);
}

Window::~Window() { destroy(); }

void Window::setup(const std::string &title, const sf::Vector2u &size) {
    closed = false;
    focused = true;
    this->title = title;

    create(size);
    //inpMgr.addCallback("WindowClose", StateType::STATE_GLOBAL, sf::Event::Closed, sf::Keyboard::A, close, this);
    //inpMgr.bindCallback("ToggleFullscreen", toggleFullscreen, this);

}

void Window::create(const sf::Vector2u &size) {
    auto style = (SharedContext::getVariables()->getVariable("Fullscreen") ? sf::Style::Fullscreen : sf::Style::Default);
    window.create(sf::VideoMode(size.x, size.y, 32), title, style);
    window.setKeyRepeatEnabled(true);
    SharedContext::getGui()->setTarget(window);
}

void Window::destroy() { window.close(); }

void Window::update() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
			window.close();
			closed = true;
			continue;
		}
		
		if (event.type == sf::Event::LostFocus) {
            focused = false;
        } else if (event.type == sf::Event::GainedFocus) {
            focused = true;
        }
        SharedContext::getGui()->handleEvent(event);
    }
}

void Window::toggleFullscreen() {
    double fullscreen = SharedContext::getVariables()->getVariable("Fullscreen");
    SharedContext::getVariables()->setVariable("Fullscreen", !fullscreen);

    destroy();
    create(window.getSize());
}

void Window::close() { closed = true; }

sf::Vector2u Window::getWindowSize() { return window.getSize(); }

sf::RenderWindow *Window::getRenderWindow() { return &window; }

bool Window::isClosed() { return closed; }

void Window::beginDraw() { window.clear(sf::Color::Black); }

void Window::endDraw() { window.display(); }

void Window::draw(sf::Drawable &drawable) { window.draw(drawable); }


//InputManager * Window::getInputManager() { return & inpMgr; }