#include "Utils/Sha512.hpp"

std::string Sha512::hash(const std::string &str) {

    if (!SHA512_Init(&context))
    {
        SysLog::Print(SysLog::Severity::Error, "[SHA512] Init() error.");
        throw std::runtime_error("[SHA512] Init() error.");
    }

    if (!SHA512_Update(&context, str.c_str(), str.length()))
    {
        SysLog::Print(SysLog::Severity::Error, "[SHA512] Update() error.");
        throw std::runtime_error("[SHA512] Update() error.");
    }

    if (!SHA512_Final(md, &context))
    {
        SysLog::Print(SysLog::Severity::Error, "[SHA512] Final() error.");
        throw std::runtime_error("[SHA512] Final() error.");
    }

    std::stringstream shastr;
    shastr << std::hex << std::setfill('0');
    for (const auto &byte: md) {
        shastr << std::setw(2) << (int) byte;
    }
    return shastr.str();
}

unsigned char Sha512::md[SHA512_DIGEST_LENGTH];
SHA512_CTX Sha512::context;
