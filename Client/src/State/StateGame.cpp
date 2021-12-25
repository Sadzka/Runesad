//
// Created by Sadza on 13.06.2021.
//

#include "State/StateGame.hpp"
#include "Base/SharedContext.hpp"

StateGame::StateGame() : State("Game"), eTime(0), dTime(0) {

}

StateGame::~StateGame() {

}

void StateGame::onCreate() {}

void StateGame::onDestroy() {}

void StateGame::activate() {
    // SharedContext::getGui()->removeAllWidgets();

}

void StateGame::deactivate() {}

void StateGame::update(const float &dTime) {
    eTime += dTime;
    this->dTime = dTime;

    Direction dir = Direction::None;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    { dir = Direction::Up; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  { dir = Direction::Down; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { dir = Direction::Right; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  { dir = Direction::Left; }

    auto optEnt = SharedContext::getEntityManager()->getEntity(playerId);
    if (optEnt.has_value())
    {
        ClientEntity *player = optEnt.value();

        if (dir == Direction::None) { player->stop(); }
        else { player->move(dir); }
    }

}

void StateGame::draw() {
    SharedContext::getWorld()->draw();
}

void StateGame::lateDraw() {
    SharedContext::getWorld()->lateDraw();
}
