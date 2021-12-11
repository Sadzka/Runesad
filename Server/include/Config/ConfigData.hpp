//
// Created by Sadza on 21.08.2021.
//

#ifndef SADZA_CONFIGDATA_HPP
#define SADZA_CONFIGDATA_HPP

#include <SFML/Config.hpp>
#include <string>

struct ConfigData {
    // std::string passphrase;
    sf::Uint16 authenticatePort;
    sf::Uint16 listenPort;
};


#endif //SADZA_CONFIGDATA_HPP
