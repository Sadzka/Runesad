//
// Created by Sadza on 12.06.2021.
//

#include "Audio/AudioManager.hpp"
#include "Base/SharedContext.hpp"

AudioManager::AudioManager() : view(nullptr) {
    maxChannels = SharedContext::getVariables()->getVariable("SoundChannels");
    if (maxChannels > 64) {
        maxChannels = 64;
        SharedContext::getVariables()->setVariable("SoundChannels", 64);
    } else if (maxChannels < 16) {
        maxChannels = 16;
        SharedContext::getVariables()->setVariable("SoundChannels", 16);
    }
    sound = new Sound[maxChannels];

    float musicVolume = SharedContext::getVariables()->getVariable("MusicVolume");
    float globalVolume = SharedContext::getVariables()->getVariable("GlobalVolume");
    music.setVolume(100 * musicVolume * globalVolume);
}

AudioManager::~AudioManager() {
    sounds.clear();
    delete[] sound;
}

void AudioManager::setView(const sf::View *view) {
    this->view = view;
}

void AudioManager::update() {

    float musicVolume = SharedContext::getVariables()->getVariable("MusicVolume");
    float globalVolume = SharedContext::getVariables()->getVariable("MusicVolume");
    float volumeMultiplier = musicVolume * globalVolume;

    for (int i = 0; i < maxChannels; ++i) {
        if (sound[i].getSound()->getStatus() == sf::Sound::Playing) {
            sound[i].setVolumeFromCenter(view->getCenter(),
                                         volumeMultiplier);
        }
    }
}

bool AudioManager::loadSound(const std::string &filename) {
    // The sound exist
    for (auto &snd : sounds) {
        if (filename == snd.first) {
            std::cerr << "AudioManager::loadSound() Sound already loaded!\n";
            return true;
        }
    }

    // The sound doesn't exists. Create it and save it.
    std::string path = "data/sounds/audio/" + filename + ".ogg";
    // The sound doesn't exists. Create it and save it.
    sf::SoundBuffer soundBuffer;
    if (soundBuffer.loadFromFile(path)) {
        sounds[filename] = soundBuffer;
        return true;
    } /*else {
        throw std::runtime_error("failed to load audio " + filename);
    }*/
    return false;
}

bool AudioManager::deleteSound(const std::string &filename) {
    auto it = sounds.find(filename);
    if (it != sounds.end()) {
        sounds.erase(it);
        return true;
    }
    return false;
}

sf::Int8 AudioManager::playSound(const std::string &soundname, sf::Vector2f position, bool loop,
                                 float maxRange) {

    auto buffer = sounds.find(soundname);
    if (buffer == sounds.end()) {
        if (!loadSound(soundname)) {
            std::cerr << "Failed load sound " << soundname << "\n";
            return -1;
        }
    }

    //find free channel
    for (int i = 0; i < maxChannels; i++) {
        sf::Sound *snd = sound[i].getSound();
        if (snd->getStatus() == sf::Sound::Stopped) {
            snd->setLoop(loop);
            snd->setBuffer(sounds[soundname]);
            sound[i].setMaxRange(maxRange);
            sound[i].setPosition(position);

            snd->play();
            return i;
        }
    }
    return -1;
}

void AudioManager::stopAllSounds() {
    for (int i = 0; i < maxChannels; ++i) {
        sound[i].getSound()->stop();
    }
}

void AudioManager::stopSound(sf::Int8 buffer) {
    sound[buffer].getSound()->stop();
}

void AudioManager::playMusic(const std::string &filename) {
    if (music.openFromFile("Data/sounds/music/" + filename + ".ogg")) {
        music.play();
    } else std::cerr << "Cant load music: " << filename << std::endl;
}

void AudioManager::setMusicLoop(const bool &loop) {
    music.setLoop(loop);
}

void AudioManager::resumeMusic() {
    music.play();
}

void AudioManager::stopMusic() {
    music.stop();
}

void AudioManager::pauseMusic() {
    music.pause();
}

void AudioManager::setMusicVolume(const float &volume) {
    SharedContext::getVariables()->setVariable("MusicVolume", volume);
    music.setVolume(100.0 *
                    SharedContext::getVariables()->getVariable("MusicVolume") *
                    SharedContext::getVariables()->getVariable("GlobalVolume"));
}

void AudioManager::setSoundsVolume(const float &volume) {
    SharedContext::getVariables()->setVariable("SoundVolume", volume);
}

void AudioManager::setGlobalVolume(const float &volume) {
    SharedContext::getVariables()->setVariable("GlobalVolume", volume);
}