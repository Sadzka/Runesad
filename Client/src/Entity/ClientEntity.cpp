//
// Created by Sadza on 19.12.2021.
//

#include "Entity/ClientEntity.hpp"

#include <Base/SharedContext.hpp>
const float speed = 48.0f;

void ClientEntity::update(const float &dTime) {
    if (!moving) { return; }
    eTime += dTime;
    if (eTime > 0.15) {
        eTime -= 0.15;
        animCrop++;

        if (animCrop > 4)
            animCrop = 0;
    }

    const float offset = dTime * speed;
    if (direction == Direction::Up) { position.y -= offset; }
    if (direction == Direction::Right) { position.x += offset; }
    if (direction == Direction::Down) { position.y += offset; }
    if (direction == Direction::Left) { position.x -= offset; }
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
            break;
        }
        case EntityType::RedTank:
        {
            const sf::Texture &texture = SharedContext::getTextureManager()->loadResource("data/img/units/redtank.png");
            sprite.setTexture(texture);
            break;
        }
        case EntityType::Missile:
        {
            const sf::Texture &texture = SharedContext::getTextureManager()->loadResource("data/img/units/missile.png");
            sprite.setTexture(texture);
            break;
        }
    }
    sprite.setOrigin(16.0f, 16.0f);
}

void ClientEntity::move(Direction dir) {
    direction = dir;
    moving = true;
}

void ClientEntity::stop() {
    moving = false;
}
