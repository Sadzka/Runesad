#include "Database/Database.hpp"
#include <fstream>

bool Database::userExist(const std::string& useraneme, const std::string& password) {
    printf("Username: %s, Password %s \n", useraneme.c_str(), password.c_str());
    std::fstream file;
    std::string filename = "Database/" + useraneme;
    file.open(filename.c_str(), std::ios::in);
    if (file.good())
    {
        std::string hashedPasword;
        file >> hashedPasword;
        file.close();

        if (password == hashedPasword) {
            return true;
        }
    }
    return false;
}
