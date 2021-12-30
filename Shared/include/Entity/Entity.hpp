#ifndef RUNESAD_ENTITY_HPP
#define RUNESAD_ENTITY_HPP


#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>
#include "Network/Messages/UpdateUnitInd.hpp"

#ifdef _CLIENT_
#include <SFML/Graphics.hpp>
#endif

enum class EntityType : sf::Uint8
{
    BlueTank = 0,
    RedTank = 1,
    Missile = 2,
    FlagBlue = 3,
    FlagRed = 4
};

class Entity {
public:
    EntityType type;
    sf::Uint32 id;
    sf::Vector2f position;
    Direction direction;
    bool moving = true;

#ifdef _CLIENT_
    sf::Sprite sprite;
    sf::Uint8 animCrop = 0;
    float eTime = 0;
public:
    void init(sf::Uint32 id, Direction dir, sf::Vector2f pos, EntityType type);
    void update(const float &dTime);
    void draw();
#endif

    sf::Uint32 getId()const { return id; }
};


#endif //RUNESAD_SERVERENTITY_HPP
