//
// Created by Sadza on 12.06.2021.
//

#pragma once

#ifndef SADZA_STRINGUTILS_HPP
#define SADZA_STRINGUTILS_HPP

#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

std::string lowercase(const std::string &str);

std::string uppercase(const std::string &str);

sf::String lowercase(const sf::String &str);

sf::String uppercase(const sf::String &str);

void toUpper(std::string &str, int start = 0, int end = -1);

void toLower(std::string &str, int start = 0, int end = -1);

/// \param str std::string& Name to validate
/// \return 0 : success <br>
/// \return 1 : Name must have at least 3 letters.<br>
/// \return 2 : Name can have up to 12 letters.<br>
/// \return 3 : Name can contain only A-Z letters.<br>
/// \return 4 : Name can have up to 2 same letters near.
///
sf::Uint8 validateName(std::string &str);

void removeExtension(std::string &str);

void getExtension(std::string &str);

#endif //SADZA_STRINGUTILS_HPP
