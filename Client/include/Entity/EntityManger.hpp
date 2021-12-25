//
// Created by Sadza on 19.12.2021.
//

#ifndef RUNESAD_ENTITYMANGER_HPP
#define RUNESAD_ENTITYMANGER_HPP

#include <unordered_map>
#include <SFML/System.hpp>
#include "Entity/ClientEntity.hpp"

class EntityManger {
    std::unordered_map<sf::Uint32, ClientEntity> entities;
public:
    std::optional<ClientEntity*> getEntity(sf::Uint32 entityId);
    void draw();
    void addEntity(const ClientEntity &entity);
    void removeEntity(sf::Uint32 entityId);
    void update(const float &dTime);
};


#endif //RUNESAD_ENTITYMANGER_HPP
