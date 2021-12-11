//
// Created by Sadza on 13.06.2021.
//

#include "Base/Exceptions.hpp"

Exception::Exception(const std::string &msg, const std::string &file, const int &line) :
    msg(msg), file(file), line(line) {
    std::cerr << what();
}

std::string Exception::what() {
    return file + ":" + std::to_string(line) + ": error: " + msg + "\n";
}
