#include "Entity/Entity.hpp"

#ifdef _CLIENT_
#include <Base/SharedContext.hpp>

void Entity::update(const float &dTime) {
    eTime += dTime;
    if (eTime > 0.3) {
        eTime -= 0.3;
        animCrop++;

        if (animCrop > 4)
            animCrop = 0;
    }
}

void Entity::draw() {
    sprite.setPosition(position);
    sprite.setTextureRect(sf::IntRect(animCrop * 32, 0, 32, 32));
    sprite.setRotation(sf::Uint8(direction)*90);
    SharedContext::getWindow()->draw(sprite);
}


void Entity::init(sf::Uint32 id, Direction dir, sf::Vector2f pos, EntityType type) {
    this->id = id;
    this->direction = Direction(dir);
    this->position = pos;
    this->type = type;

    switch (type) {
        case EntityType::BlueTank:
        {
            const sf::Texture &texture = SharedContext::getTextureManager()->getResource("data/img/units/bluetank.png");
            sprite.setTexture(texture);
            break;
        }
        case EntityType::RedTank:
        {
            const sf::Texture &texture = SharedContext::getTextureManager()->getResource("data/img/units/redtank.png");
            sprite.setTexture(texture);
            break;
        }
        case EntityType::Missile:
        {
            const sf::Texture &texture = SharedContext::getTextureManager()->getResource("data/img/units/missile.png");
            sprite.setTexture(texture);
            break;
        }
    }
}

#endif