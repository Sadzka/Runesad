//
// Created by Sadza on 12.06.2021.
//

#include "Utils/StringUtils.hpp"

std::string lowercase(const std::string &str) {
    std::string tmp = str;
    for (char &c : tmp) {
        if (c >= 'A' && c <= 'Z')
            c ^= 32;
    }
    return tmp;
}

std::string uppercase(const std::string &str) {
    std::string tmp = str;
    for (char &c : tmp) {
        if (c >= 'a' && c <= 'z')
            c ^= 32;
    }
    return tmp;
}

sf::String lowercase(const sf::String &str) {
    sf::String tmp = str;
    for (unsigned i = 0; i < tmp.getSize(); i++) {
        if (tmp[i] >= 'A' && tmp[i] <= 'Z')
            tmp[i] ^= 32;
    }
    return str;
}

sf::String uppercase(sf::String &str) {
    sf::String tmp = str;
    for (unsigned i = 0; i < str.getSize(); i++) {
        if (tmp[i] >= 'a' && tmp[i] <= 'z')
            tmp[i] ^= 32;
    }
    return tmp;
}

void toUpper(std::string &str, int start, int end) {
    if (end == -1)
        end = str.length();

    for (int i = start; i < end; i++) {
        str[i] = toupper(str[i]);
    }

}

void toLower(std::string &str, int start, int end) {
    if (end == -1)
        end = str.length();

    for (int i = start; i < end; i++) {
        str[i] = tolower(str[i]);
    }

}

sf::Uint8 validateName(std::string &str) {
    if (str.length() < 3) {
        return 1;
    }

    if (str.length() > 12) {
        return 2;
    }

    //lower
    lowercase(str);

    //check letters
    for (unsigned i = 0; i < str.length(); i++) {
        if (str[i] < 'a' || str[i] > 'z')
            return 3;
    }

    //up to 2 char near
    for (unsigned i = 0; i < str.length() - 2; i++) {
        if (str[i] == str[i + 1] && str[i] == str[i + 2])
            return 4;
    }

    toUpper(str, 0, 1);
    return 0;
}

void removeExtension(std::string &str) {
    size_t pos = str.find_last_of('.');
    str = str.substr(0, pos);
}

void getExtension(std::string &str) {
    size_t pos = str.find_last_of('.');
    str = str.substr(pos+1);
}
