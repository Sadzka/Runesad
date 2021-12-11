//
// Created by Sadza on 12.06.2021.
//

#ifndef SADZA_SOUND_HPP
#define SADZA_SOUND_HPP

#include <cmath>
#include <SFML/Audio.hpp>

class Sound {
    sf::Sound sound;
    sf::Vector2f position;
    float maxRange;
public:
    Sound();

    void setMaxRange(const float &maxRange);

    sf::Sound *getSound();

    void setPosition(const sf::Vector2f &position);

    void setVolumeFromCenter(const sf::Vector2f & center, float volumeMultiplier);
};


#endif //SADZA_SOUND_HPP
