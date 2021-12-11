#include "Graphics/TextureManager.hpp"

TextureManager::TextureManager() {

}

TextureManager::~TextureManager() {
    textures.clear();
}

const sf::Texture &TextureManager::getResource(const std::string &filename) {
    for (auto it = textures.begin(); it != textures.end(); it++) {
        if (filename == it->first)
            return it->second;

    }

#ifdef __DEBUG
    std::cerr << "GAME_ERROR: Texture was not found. It is filled with an empty image.\n";
    sf::Texture texture;
    textures[filename] = texture;
    return textures[filename];
#else
    throw std::runtime_error("Couldn't load texture: " + filename);
#endif // __DEBUG
}

const sf::Texture &TextureManager::loadResource(const std::string &filename) {
    // The image exist
    for (auto it = textures.begin(); it != textures.end(); it++) {
        if (filename == it->first) {
            return it->second;
        }
    }

    // The image doesen't exists. Create it and save it.
    sf::Texture texture;
    if (texture.loadFromFile(filename)) {
        textures[filename] = texture;
        return textures[filename];
    } else
        throw locationException("Couldn't load texture: " + filename);
}

void TextureManager::deleteResource(const std::string &filename) {
    auto it = textures.find(filename);
    if (it != textures.end())
        textures.erase(it);
}
