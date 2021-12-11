//
// Created by Sadza on 12.06.2021.
//

#include "Audio/Sound.hpp"

Sound::Sound() {

}

void Sound::setMaxRange(const float &maxRange) {
    this->maxRange = maxRange;
}

void Sound::setPosition(const sf::Vector2f &position) {
    this->position = position;
}

sf::Sound *Sound::getSound() {
    return &sound;
}

#include <iostream>
void Sound::setVolumeFromCenter(const sf::Vector2f &center, float volumeMultiplier) {
    sf::Vector2f distance = { center.x - position.x, center.y - position.y };
    float distance_flat = sqrt(distance.x * distance.x + distance.y * distance.y);
    float volume = (maxRange - distance_flat)/maxRange;
    if (volume < 0) { volume = 0; }
    std::cout << volume << std::endl;
    sound.setVolume(volume > 0 ? volume * volumeMultiplier * 100 : 0);
}
