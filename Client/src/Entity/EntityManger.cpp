//
// Created by Sadza on 19.12.2021.
//

#include <Entity/Entity.hpp>
#include "Entity/EntityManger.hpp"

std::optional<ClientEntity*> EntityManger::getEntity(sf::Uint32 entityId) {
    auto itr = entities.find(entityId);
    if (itr == entities.end()) return std::nullopt;
    return &itr->second;
}

void EntityManger::addEntity(const ClientEntity &entity) {
    entities.emplace(std::make_pair(entity.getId(), entity));
}

void EntityManger::update(const float &dTime) {
    for (auto &entity : entities) {
        entity.second.update(dTime);
    }
}

void EntityManger::draw() {
    for (auto &entity : entities) {
        entity.second.draw();
    }
}

void EntityManger::removeEntity(sf::Uint32 entityId) {
    auto itr = entities.find(entityId);
    if (itr == entities.end()) return;
    entities.erase(itr);
}
