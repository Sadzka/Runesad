#include "State/base/ScreenAnimation.hpp"
#include <Utils/AnimationUtils.hpp>
#include <Base/SharedContext.hpp>

ScreenAnimation::ScreenAnimation() : inAction(false) {

}

void ScreenAnimation::startAnimation(const ScreenAnimation::Direction &direction, const sf::Time &_duration) {
    eTime = sf::seconds(0);
    inAction = true;
    duration = _duration;
    widgetsBasePosition.clear();
    offset.x = SharedContext::getWindow()->getRenderWindow()->getSize().x;
    offset.y = SharedContext::getWindow()->getRenderWindow()->getSize().y;
    if (direction == Direction::Right) {
        offset.y = 0;
    }
    else if (direction == Direction::Left) {
        offset.x = -offset.x;
        offset.y = 0;
    }
    else if (direction == Direction::Down) {
        offset.x = -0;
    }
    else if (direction == Direction::Up) {
        offset.x = -0;
        offset.y = -offset.y;
    }

    for (auto &widget : SharedContext::getGui()->getWidgets()) {
        widgetsBasePosition.push_back(widget->getPosition());
    }
}

void ScreenAnimation::update(const sf::Time &time) {
    if (!inAction) return;

    eTime += time;
    if (eTime > duration) {
        inAction = false;
        int i = 0;
        for (auto &widget : SharedContext::getGui()->getWidgets()) {
            widget->setPosition(widgetsBasePosition[i].x + offset.x,
                                widgetsBasePosition[i].y + offset.y);
            i++;
        }
    }

    float animationSpeed = utils::parametricBlend(eTime.asSeconds() / duration.asSeconds());

    sf::Vector2f move = {animationSpeed * offset.x, animationSpeed * offset.y};

    int i = 0;
    for (auto &widget : SharedContext::getGui()->getWidgets()) {
        widget->setPosition(widgetsBasePosition[i].x + move.x,
                            widgetsBasePosition[i].y + move.y);
        i++;
    }
}
