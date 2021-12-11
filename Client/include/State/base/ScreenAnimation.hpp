#ifndef RUNESAD_SCREENANIMATION_HPP
#define RUNESAD_SCREENANIMATION_HPP

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

class ScreenAnimation
{
public:
    std::vector < sf::Vector2f > widgetsBasePosition;
    bool inAction;
    sf::Time duration;
    sf::Vector2f offset;
    sf::Time eTime;

    enum Direction {
        Left,
        Right,
        Down,
        Up
    };

    ScreenAnimation();
    void startAnimation(const Direction &direction, const sf::Time &_duration);
    void update(const sf::Time &time);

};

#endif //RUNESAD_SCREENANIMATION_HPP
