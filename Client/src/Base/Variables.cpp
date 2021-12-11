//
// Created by Sadza on 12.06.2021.
//

#include "Base/Variables.hpp"

void Variables::loadFromFile(const std::string &path) {
    std::fstream file;
    std::string line;
    std::string keyword;
    double value;
    file.open(path, std::ios::in);

    if (file.good()) {
        while (getline(file, line)) {
            std::stringstream ss(line);
            ss >> keyword;
            if (keyword == "SET") {
                if (!(ss >> keyword)) continue;
                if (!(ss >> value)) continue;
                lowercase(keyword);
                setVariable(keyword, value);
            }
        }
    }
    file.close();
}
#include "iostream"
void Variables::loadDefault(void) {
    addVariable("fullscreen", 0);
    addVariable("maxfps", 60);
    addVariable("globalvolume", 1.0);
    addVariable("soundvolume", 1.0);
    addVariable("musicvolume", 1.0);
    addVariable("soundchannels", 64);
    addVariable("vsync", 0);
    addVariable("_tilesize", 32);
}

void Variables::save(void) {
    std::fstream file;
    std::string str;

    file.open("Data/Config/vars.txt", std::ios::out);
    if (file.good()) {
        for (auto &itr : variables) {
            file << "SET " << itr.first << ' ' << itr.second << '\n';
        }
    }
    file.close();
}

Variables::Variables() {
    loadDefault();
    //loadFromFile("Data/Config/vars.txt");
}

Variables::~Variables() {
    save();
}

void Variables::addVariable(const std::string &name, const double &value) {
    variables.insert(std::make_pair(name, value));
}

bool Variables::setVariable(const std::string &name, const double &value) {
    if (name[0] == '_') return false;
    auto x = variables.find(lowercase(name));
    if (x == variables.end()) return false;
    x->second = value;
    return true;
}

double Variables::getVariable(const std::string &name) {
    auto x = variables.find(lowercase(name));
    if (x == variables.end()) throw std::runtime_error("getVariable()\nTrying to get unknown variable!\n");
    return x->second;
}
