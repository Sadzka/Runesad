//
// Created by Sadza on 19.12.2021.
//

#ifndef RUNESAD_ENTITYMANGER_HPP
#define RUNESAD_ENTITYMANGER_HPP

#include <vector>
#include <SFML/System.hpp>
#include "Entity/ClientEntity.hpp"

class EntityManger {
    std::vector<std::shared_ptr<ClientEntity>> entities;
    sf::Mutex mutex;
public:
    std::optional<std::shared_ptr<ClientEntity>> getEntity(sf::Uint32 entityId);
    void draw();
    void addEntity(const ClientEntity &entity);
    void removeEntity(sf::Uint32 entityId);
    void update(const float &dTime);

    void clearAll();
};


#endif //RUNESAD_ENTITYMANGER_HPP
