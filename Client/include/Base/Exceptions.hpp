//
// Created by Sadza on 13.06.2021.
//

#pragma once

#ifndef SADZA_EXCEPTIONS_HPP
#define SADZA_EXCEPTIONS_HPP


#include <cstring>
#include <iostream>

#define locationException(arg) Exception(arg, __FILE__, __LINE__);

class Exception {
public:
    Exception(const std::string & msg, const std::string & file, const int & line);
    std::string what();

private:
    std::string msg;
    std::string file;
    int line;
};


#endif //SADZA_EXCEPTIONS_HPP
