#ifndef RUNESAD_DATABASE_HPP
#define RUNESAD_DATABASE_HPP

#include <string>

class Database {
public:
    static bool userExist(const std::string& useraneme, const std::string& password);
};


#endif //RUNESAD_DATABASE_HPP
