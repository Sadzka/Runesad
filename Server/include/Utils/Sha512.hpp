//
// Created by Sadza on 21.08.2021.
//

#ifndef SADZA_Sha512_HPP
#define SADZA_Sha512_HPP

#include "Sys/SysLog.hpp"

#include <openssl/sha.h>

#include <sstream>
#include <iomanip>

class Sha512 {
public:
    static std::string hash(const std::string &str);

private:
    static unsigned char md[SHA512_DIGEST_LENGTH];
    static SHA512_CTX context;
};

#endif //SADZA_Sha512_HPP
