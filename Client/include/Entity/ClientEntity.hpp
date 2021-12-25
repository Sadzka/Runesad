//
// Created by Sadza on 19.12.2021.
//

#ifndef RUNESAD_CLIENTENTITY_HPP
#define RUNESAD_CLIENTENTITY_HPP

#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>
#include "Network/Messages/UpdateUnitInd.hpp"

#include <SFML/Graphics.hpp>
#include <Entity/Entity.hpp>

class ClientEntity {
    friend class Messenger;
    EntityType type;
    sf::Uint32 id;
    sf::Vector2f position;
    Direction direction;
    bool moving = false;

    sf::Sprite sprite;
    sf::Uint8 animCrop = 0;
    float eTime = 0;
public:
    void init(sf::Uint32 id, Direction dir, sf::Vector2f pos, EntityType type);
    void update(const float &dTime);
    void draw();
    void move(Direction dir);
    void stop();
    sf::Uint32 getId()const { return id; }
};


#endif //RUNESAD_CLIENTENTITY_HPP
