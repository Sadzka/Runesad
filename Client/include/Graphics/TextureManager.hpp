//
// Created by Sadza on 13.06.2021.
//

#pragma once

#ifndef SADZA_TEXTUREMANAGER_HPP
#define SADZA_TEXTUREMANAGER_HPP

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <string>
#include <iostream>
#include "Base/Exceptions.hpp"

class TextureManager {
public:
    TextureManager();

    ~TextureManager();

    TextureManager(const TextureManager &) = delete;

    const sf::Texture &getResource(const std::string &filename);

    const sf::Texture &loadResource(const std::string &filename);

    void deleteResource(const std::string &filename);

private:
    std::unordered_map<std::string, sf::Texture> textures;
};

#endif //SADZA_TEXTUREMANAGER_HPP
