#include "Config/ConfigLoader.hpp"

ConfigLoader::ConfigLoader(const std::string &path, ConfigData &cfg) {
    serialize(path, cfg);
}

void ConfigLoader::serialize(const std::string &path, ConfigData &cfg) {
    std::fstream file;
    file.open(path, std::ios::in);

    if (!file.is_open()) {
        file.close();
        SysLog::Print(SysLog::Severity::Error, "[ConfigLoader] Failed open file: %s.", path.c_str());
        throw std::runtime_error("[ConfigLoader] Failed open file: " + path);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string keyword, value;
        ss >> keyword >> value;
        items.insert({keyword, value});
    }

    serialize("AuthenticatePort", cfg.authenticatePort);
    serialize("ListenPort", cfg.listenPort);
    file.close();
}

template <typename T>
void ConfigLoader::serialize(const std::string &name, T &ref) {
    auto value = items.find(name);
    if (value == items.end()) {
        SysLog::Print(SysLog::Severity::Error, "[ConfigLoader] `%s` not found in config.", name.c_str());
        throw std::runtime_error("[ConfigLoader] " + name + " not found in config.");
    }
    assignItem(value->second, ref);
}

void ConfigLoader::assignItem(const std::string &value, char *ref) {
    memcpy(ref, value.c_str(), value.length());
}

void ConfigLoader::assignItem(const std::string &value, std::string &ref) { ref = value; }


void ConfigLoader::assignItem(const std::string &value, float &ref) { ref = std::stof(value); }
void ConfigLoader::assignItem(const std::string &value, double &ref) { ref = std::stod(value); }
void ConfigLoader::assignItem(const std::string &value, long double &ref) { ref = std::stold(value); }

void ConfigLoader::assignItem(const std::string &value, short &ref) { ref = static_cast<short>(std::stoi(value)); }
void ConfigLoader::assignItem(const std::string &value, unsigned short &ref) { ref = static_cast<unsigned short>(std::stoul(value)); }

void ConfigLoader::assignItem(const std::string &value, long &ref) { ref = std::stol(value); }
void ConfigLoader::assignItem(const std::string &value, unsigned long &ref) { ref = std::stoul(value); }

void ConfigLoader::assignItem(const std::string &value, long long &ref) { ref = std::stoll(value); }
void ConfigLoader::assignItem(const std::string &value, unsigned long long &ref) { ref = std::stoull(value); }

