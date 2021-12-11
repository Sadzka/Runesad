//
// Created by Sadza on 12.06.2021.
//

#ifndef SADZA_AUDIOMANAGER_HPP
#define SADZA_AUDIOMANAGER_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics/View.hpp>
#include <unordered_map>
#include <iostream>

#include "Audio/Sound.hpp"

class AudioManager {
    const sf::View *view;

    int maxChannels;
    std::unordered_map<std::string, sf::SoundBuffer> sounds;
    Sound *sound;

    sf::Music music;

public:
    AudioManager();

    ~AudioManager();

    AudioManager(const AudioManager &) = delete;

    void setView(const sf::View *view);

    void update();

    sf::Int8 playSound(const std::string &soundname, sf::Vector2f position, bool loop = false,
                       float maxRange = 800);

    bool loadSound(const std::string &filename);

    void stopAllSounds();

    void stopSound(sf::Int8 buffer);

    bool deleteSound(const std::string &filename);

    void setMusicLoop(const bool &loop);

    void playMusic(const std::string &filename);

    void stopMusic();

    void pauseMusic();

    void resumeMusic();

    void setSoundsVolume(const float &volume);

    void setMusicVolume(const float &volume);

    void setGlobalVolume(const float &volume);
};


#endif //SADZA_AUDIOMANAGER_HPP
