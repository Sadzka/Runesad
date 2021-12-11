#ifndef SADZA_CONFIGLOADER_HPP
#define SADZA_CONFIGLOADER_HPP

#include "Config/ConfigData.hpp"
#include "Sys/SysLog.hpp"
#include <unordered_map>
#include <fstream>
#include <sstream>

class ConfigLoader {
public:
    ConfigLoader(const std::string &path, ConfigData &configData);
private:
    std::unordered_map <std::string, std::string> items;
    void serialize(const std::string &path, ConfigData & cfg);

    template <typename T>
    void serialize(const std::string &name, T &value);

    void static assignItem(const std::string &name, char *value);
    void static assignItem(const std::string &name, std::string &value);

    void static assignItem(const std::string &name, float &value);
    void static assignItem(const std::string &name, double &value);
    void static assignItem(const std::string &name, long double &value);

    void static assignItem(const std::string &name, short &value);
    void static assignItem(const std::string &name, unsigned short &value);

    void static assignItem(const std::string &name, long &value);
    void static assignItem(const std::string &name, unsigned long &value);

    void static assignItem(const std::string &name, long long &value);
    void static assignItem(const std::string &name, unsigned long long &value);
};

#endif //SADZA_CONFIGLOADER_HPP
