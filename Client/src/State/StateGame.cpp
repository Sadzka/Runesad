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

    endButton = tgui::Button::create("Placeholder");
    endButton->setSize({"200", "36"});
    endButton->setPosition({"50% - 100", "50% - 18"});
    endButton->setVisible(false);
    endButton->onPress([=]() {
        SharedContext::getStateManager()->switchTo(StateType::Main);
//        StateMain *state = (StateMain*)(SharedContext::getStateManager()->getCurrentState());
//        state->screenAnimation.startAnimation(ScreenAnimation::Direction::Right, sf::seconds(0.25));
    });

    SharedContext::getGui()->add(endButton, "endButton");
}

void StateGame::deactivate() {
    auto endButton = SharedContext::getGui()->get<tgui::Button>("endButton");
    if (endButton) SharedContext::getGui()->remove(endButton);
}

void StateGame::update(const float &dTime) {

    eTime += dTime;
    this->dTime = dTime;

    if (endButton->isVisible()) return;
    shotCd -= dTime;

    Direction dir = Direction::None;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    { dir = Direction::Up; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  { dir = Direction::Down; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { dir = Direction::Right; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  { dir = Direction::Left; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shotCd <= 0.0) { SharedContext::getClient()->sendShotInd(); shotCd = 1.0f; }

    auto optEnt = SharedContext::getEntityManager()->getEntity(playerId);
    if (optEnt.has_value())
    {
        std::shared_ptr<ClientEntity> player = optEnt.value();

        if (dir == Direction::None) {
            if (player->isMoving()) { SharedContext::getClient()->sendMoveInd(false); }
        }
        else {
            if (!(player->isMoving() && player->getDirection() == dir))
                SharedContext::getClient()->sendMoveInd(true, dir);
        }
    }

}

void StateGame::draw() {
    SharedContext::getWorld()->draw();
}

void StateGame::lateDraw() {
    SharedContext::getWorld()->lateDraw();
}
