//
// Created by Sadza on 19.08.2021.
//

#ifndef SADZA_CLIENT_SOCKETIMPL_HPP
#define SADZA_CLIENT_SOCKETIMPL_HPP

#include <Network/Socket/Socket.hpp>
#include <cstring>

#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

#include <openssl/ssl.h>

namespace ssf {
    namespace priv {
        class SocketImpl {
        public:

            typedef int AddrLength;

            static sockaddr_in createAddress(sf::Uint32 address, unsigned short port);

            static SocketHandle invalidSocket();

            static void close(SocketHandle sock);

            static void setBlocking(SocketHandle sock, bool block);

            static ssf::Socket::Status getErrorStatus();
        };

    }

} // namespace priv


#endif //SADZA_CLIENT_SOCKETIMPL_HPP
