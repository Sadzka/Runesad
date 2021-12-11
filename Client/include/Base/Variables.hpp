//
// Created by Sadza on 12.06.2021.
//

#pragma once

#ifndef SADZA_VARIABLES_HPP
#define SADZA_VARIABLES_HPP

#include <fstream>
#include <sstream>
#include <unordered_map>
#include "Utils/StringUtils.hpp"

class Variables {
    std::unordered_map<std::string, double> variables;

    void loadFromFile(const std::string &path);

    void loadDefault(void);

    void save(void);

    void addVariable(const std::string &name, const double &value);

public:
    Variables();

    ~Variables();

    bool setVariable(const std::string &name, const double &value);

    double getVariable(const std::string &name);
};

#endif //SADZA_VARIABLES_HPP
