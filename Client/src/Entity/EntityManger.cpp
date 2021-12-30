//
// Created by Sadza on 19.12.2021.
//

#include <Entity/Entity.hpp>
#include <Base/SharedContext.hpp>
#include "Entity/EntityManger.hpp"
#include <algorithm>

std::optional<std::shared_ptr<ClientEntity>> EntityManger::getEntity(sf::Uint32 entityId) {

    mutex.lock();
    auto itr = std::find_if(entities.begin(), entities.end(), [&entityId](const std::shared_ptr<ClientEntity>& entity) {
        return entity->getId() == entityId;
    });
    mutex.unlock();
    if (itr == entities.end()) return std::nullopt;
    return *itr;
}

void EntityManger::addEntity(const ClientEntity &entity) {
    mutex.lock();
    SysLog::Print(SysLog::Severity::Info, "Entity added id=[%u], type=[%u], pos=[%u, %u] \n",
                  entity.getId(), entity.getType(), entity.getPosition().x, entity.getPosition().y);
    entities.push_back(std::make_shared<ClientEntity>(entity));
    mutex.unlock();
}

void EntityManger::update(const float &dTime) {
    mutex.lock();
    for (auto &entity : entities) {
        entity->update(dTime);
    }

    // Check Missle Collisions
    for (int i = 0; i < entities.size(); ++i) {
        for (int j = i + 1; j < entities.size(); ++j) {
            if (!entities[i]->isUpdatable()) continue;
            if (!entities[j]->isUpdatable()) continue;

            sf::Vector2f missilePos = entities[i]->getPosition();
            if (entities[j]->getGlobalBounds().contains(missilePos.x - 5, missilePos.y - 5)
            ||  entities[j]->getGlobalBounds().contains(missilePos.x + 5, missilePos.y - 5)
            ||  entities[j]->getGlobalBounds().contains(missilePos.x + 5, missilePos.y + 5)
            ||  entities[j]->getGlobalBounds().contains(missilePos.x - 5, missilePos.y + 5))
            {
                entities[i]->markDestroyed();
                entities[j]->markDestroyed();
                SharedContext::getClient()->sendDestroy(entities[i]->getId());
                SharedContext::getClient()->sendDestroy(entities[j]->getId());
                break;
            }
        }
    }
    mutex.unlock();
}

void EntityManger::draw() {
    mutex.lock();
    for (auto &entity : entities) {
        entity->draw();
    }
    mutex.unlock();
}

void EntityManger::removeEntity(sf::Uint32 entityId) {
    mutex.lock();
    auto itr = std::find_if(entities.begin(), entities.end(), [&entityId](const std::shared_ptr<ClientEntity>& entity) {
        return entity->getId() == entityId;
    });
    if (itr == entities.end()) {
        return;
    }
    entities.erase(itr);
    mutex.unlock();
}

void EntityManger::clearAll() {
    mutex.lock();
    entities.clear();
    mutex.unlock();
}
