//
// Created by Sadza on 13.06.2021.
//

#include "State/StateGame.hpp"
#include "Base/SharedContext.hpp"

StateGame::StateGame() : State("Game"), eTime(0), dTime(0) {
//    world = new World(shrd->wind->getRenderWindow(), shrd->txtMgr);
//    world->loadWorld("null");
//    SharedContext::getWorld()->loadWorld("Main");
}

StateGame::~StateGame() {

}

void StateGame::onCreate() {}

void StateGame::onDestroy() {}

void StateGame::activate() {}

void StateGame::deactivate() {}

void StateGame::update(const float &dTime) {
    eTime += dTime;
    this->dTime = dTime;
}

void StateGame::draw() {
    SharedContext::getWorld()->draw();
}

void StateGame::lateDraw() {
    SharedContext::getWorld()->lateDraw();
}
