//
// Created by Sadza on 19.12.2021.
//

#include "Entity/ClientEntity.hpp"

#include <Base/SharedContext.hpp>


void ClientEntity::update(const float &dTime) {
    if (!updatable) return;

    if (type == EntityType::FlagBlue || type == EntityType::FlagRed) { return; }

    sf::Vector2f entitySize;
    float speed;
    switch (type)
    {
        case EntityType::BlueTank:
        case EntityType::RedTank:
            entitySize.x = 12;
            entitySize.y = 12;
            speed = 80.0f;
            break;
        case EntityType::Missile:
            entitySize.x = 4;
            entitySize.y = 4;
            speed = 300.0f;
            break;
    }

    if (!moving) { return; }
    eTime += dTime;

    sf::Vector2f targetPosition = position;
    sf::Vector2f targetPositionWithEntitySize = position;
    const float offset = dTime * speed;
    if (direction == Direction::Up) {
        targetPosition.y -= offset;
        targetPositionWithEntitySize.y = targetPosition.y - entitySize.y;
    }
    if (direction == Direction::Right) {
        targetPosition.x += offset;
        targetPositionWithEntitySize.x = targetPosition.x + entitySize.x;
    }
    if (direction == Direction::Down) {
        targetPosition.y += offset;
        targetPositionWithEntitySize.y = targetPosition.y + entitySize.y;
    }
    if (direction == Direction::Left) {
        targetPosition.x -= offset;
        targetPositionWithEntitySize.x = targetPosition.x - entitySize.x;
    }

    if (type == EntityType::Missile)
    {
        if (SharedContext::getWorld()->isPossitionDestroyable(targetPositionWithEntitySize)) {
            SharedContext::getClient()->sendDestroyTile(targetPositionWithEntitySize);
            SharedContext::getClient()->sendDestroy(id);
            updatable = false;
            return;
        }
        else if (SharedContext::getWorld()->isPossitionDestroyingMissle(targetPositionWithEntitySize)) {
            SharedContext::getClient()->sendDestroy(id);
            updatable = false;
            return;
        }
    }
    else
    {
        if (SharedContext::getWorld()->isPossitionCollidable(targetPositionWithEntitySize)) { return; }
        if (eTime > 0.15) {
            eTime -= 0.15;
            animCrop++;

            if (animCrop > 4)
                animCrop = 0;
        }
    }
    position = targetPosition;
}

void ClientEntity::draw() {
    sprite.setPosition(position);
    sprite.setTextureRect(sf::IntRect(animCrop * 32, 0, 32, 32));
    sprite.setRotation(sf::Uint8(direction)*90);
    SharedContext::getWindow()->draw(sprite);
}

void ClientEntity::init(sf::Uint32 id, Direction dir, sf::Vector2f pos, EntityType type) {
    this->id = id;
    this->direction = Direction(dir);
    this->position = pos;
    this->type = type;

    switch (type) {
        case EntityType::BlueTank:
        {
            const sf::Texture &texture = SharedContext::getTextureManager()->loadResource("Data/img/units/bluetank.png");
            sprite.setTexture(texture);
            sprite.setOrigin(16.0f, 16.0f);
            break;
        }
        case EntityType::RedTank:
        {
            const sf::Texture &texture = SharedContext::getTextureManager()->loadResource("data/img/units/redtank.png");
            sprite.setTexture(texture);
            sprite.setOrigin(16.0f, 16.0f);
            break;
        }
        case EntityType::Missile:
        {
            const sf::Texture &texture = SharedContext::getTextureManager()->loadResource("data/img/units/missile.png");
            sprite.setTexture(texture);
            sprite.setOrigin(6.0f, 6.0f);
            moving = true;
            break;
        }
        case EntityType::FlagBlue:
        {
            const sf::Texture &texture = SharedContext::getTextureManager()->loadResource("data/img/units/blueflag.png");
            sprite.setTexture(texture);
            sprite.setOrigin(16.0f, 16.0f);
            break;
        }
        case EntityType::FlagRed:
        {
            const sf::Texture &texture = SharedContext::getTextureManager()->loadResource("data/img/units/redflag.png");
            sprite.setTexture(texture);
            sprite.setOrigin(16.0f, 16.0f);
            break;
        }
    }
}

void ClientEntity::move(Direction dir) {
    direction = dir;
    moving = true;
}

void ClientEntity::stop() {
    moving = false;
}
