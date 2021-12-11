#include "Network/Socket/TslListener.hpp"
#include "Network/Socket/SocketImpl.hpp"

namespace ssf {
    TslListener::TslListener() :
            Socket(Tcp) {
    }

    unsigned short TslListener::getLocalPort() const {
        if (getHandle() != priv::SocketImpl::invalidSocket()) {
            // Retrieve informations about the local end of the socket
            sockaddr_in address;
            priv::SocketImpl::AddrLength size = sizeof(address);
            if (getsockname(getHandle(), reinterpret_cast<sockaddr *>(&address), &size) != -1) {
                return ntohs(address.sin_port);
            }
        }

        // We failed to retrieve the port
        return 0;
    }

    Socket::Status TslListener::listen(unsigned short port, const sf::IpAddress &address) {
        // Close the socket if it is already bound
        close();

        // Create the internal socket if it doesn't exist
        create();

        // Check if the address is valid
        if ((address == sf::IpAddress::None) || (address == sf::IpAddress::Broadcast))
            return Error;

        // Bind the socket to the specified port
        sockaddr_in addr = priv::SocketImpl::createAddress(address.toInteger(), port);
        if (bind(getHandle(), reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) == -1) {
            // Not likely to happen, but...
            std::cerr << "Failed to bind listener socket to port " << port << std::endl;
            return Error;
        }

        // Listen to the bound port
        if (::listen(getHandle(), SOMAXCONN) == -1) {
            // Oops, socket is deaf
            std::cerr << "Failed to listen to port " << port << std::endl;
            return Error;
        }

        return Done;
    }

    void TslListener::close() {
        // Simply close the socket
        Socket::close();
    }

    Socket::Status TslListener::accept(TslSocket &socket) {
        // Make sure that we're listening
        if (getHandle() == priv::SocketImpl::invalidSocket()) {
            std::cerr << "Failed to accept a new connection, the socket is not listening" << std::endl;
            return Error;
        }

        // Accept a new connection
        sockaddr_in address;
        priv::SocketImpl::AddrLength length = sizeof(address);
        SocketHandle remote = ::accept(getHandle(), reinterpret_cast<sockaddr *>(&address), &length);

        // Check for errors
        if (remote == priv::SocketImpl::invalidSocket())
            return priv::SocketImpl::getErrorStatus();

        // Accept SSL connection
        socket.ssl = SSL_new(socket.ctx);
        if (socket.ssl == NULL) throw std::runtime_error("Failed SSL_new().");
        SSL_set_fd(socket.ssl, remote);
        int acc = SSL_accept(socket.ssl);
        if (acc == -1) {
            //throw std::runtime_error("Failed SSL_accept().");
        }
        // Initialize the new connected socket
        socket.close();
        socket.create(remote);

        return Done;
    }
}