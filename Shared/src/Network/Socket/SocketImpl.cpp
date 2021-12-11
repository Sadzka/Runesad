#include "Network/Socket/SocketImpl.hpp"

namespace ssf {
    namespace priv {
        sockaddr_in SocketImpl::createAddress(sf::Uint32 address, unsigned short port) {
            sockaddr_in addr;
            std::memset(&addr, 0, sizeof(addr));
            addr.sin_addr.s_addr = htonl(address);
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);

            return addr;
        }

        SocketHandle SocketImpl::invalidSocket() {
            return INVALID_SOCKET;
        }

        void SocketImpl::close(SocketHandle sock) {
            closesocket(sock);

        }

        void SocketImpl::setBlocking(SocketHandle sock, bool block) {
            u_long blocking = block ? 0 : 1;
            ioctlsocket(sock, FIONBIO, &blocking);
        }

        Socket::Status SocketImpl::getErrorStatus() {
            switch (WSAGetLastError()) {
                case WSAEWOULDBLOCK:
                    return Socket::NotReady;
                case WSAEALREADY:
                    return Socket::NotReady;
                case WSAECONNABORTED:
                    return Socket::Disconnected;
                case WSAECONNRESET:
                    return Socket::Disconnected;
                case WSAETIMEDOUT:
                    return Socket::Disconnected;
                case WSAENETRESET:
                    return Socket::Disconnected;
                case WSAENOTCONN:
                    return Socket::Disconnected;
                case WSAEISCONN:
                    return Socket::Done; // when connecting a non-blocking socket
                default:
                    return Socket::Error;
            }
        }

        struct SocketInitializer {
            SocketInitializer() {
                OpenSSL_add_ssl_algorithms();

                #ifdef WIN32
                static WSADATA init;
                if (WSAStartup(MAKEWORD(2, 2), &init) != 0) {
                    throw std::runtime_error("WSAStartup failed");
                }
                #endif
            }

            ~SocketInitializer() {
                #ifdef WIN32
                WSACleanup();
                #endif
            }
        };

        SocketInitializer globalInitializer;
    }
}
