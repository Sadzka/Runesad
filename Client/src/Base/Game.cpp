#include "Base/Game.hpp"

void Game::FPSLimit() {
    float time = deltaTime.asSeconds();
    printf("time: %u \n", time);
    fps_clock += time;

    frames++;
    if (fps_clock > 1.0f) {
        printf("FPS: %u \n", frames);
        frames = 0;
        fps_clock = 0.0f;
    }
}

Game::Game() : fps_clock(0) {
    deltaTime = sf::seconds(0);
    Window * window = SharedContext::getWindow();
    Variables * vars = SharedContext::getVariables();

    bool vsync = vars->getVariable("vsync");
    if (vsync) window->getRenderWindow()->setVerticalSyncEnabled(vsync);
    else window->getRenderWindow()->setFramerateLimit(vars->getVariable("MaxFPS"));

    SharedContext::getAudioManager()->setView(&window->getRenderWindow()->getView());
    window->init("Arikazike", sf::Vector2u(1366, 768));

    SharedContext::getStateManager()->switchTo(StateType::Main);
    SharedContext::getGui()->setTarget(*window->getRenderWindow());
}

Game::~Game() {
//    shared.client->disconnect();
//    shared.client->unbound();
    SharedContext::getAudioManager()->stopAllSounds();
    SharedContext::getAudioManager()->stopMusic();
}

void Game::update() {
    // FPSLimit();
    deltaTime = clock.restart();
    float dTime = deltaTime.asSeconds();

    SharedContext::getStateManager()->update(dTime);
    SharedContext::getWindow()->update();
    SharedContext::getAudioManager()->update();
    SharedContext::getGui()->updateTime();
    lateUpdate();
}

void Game::render() {
    SharedContext::getWindow()->beginDraw();

    SharedContext::getStateManager()->draw();
    SharedContext::getGui()->draw();
    //SharedContext::getEntityManager()->draw();
    SharedContext::getStateManager()->lateDraw();

    SharedContext::getWindow()->endDraw();
}

void Game::lateUpdate() {
}

void Game::restartClock() {
}

Window * Game::getWindow() {
    return SharedContext::getWindow();
}
