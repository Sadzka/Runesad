#include "Network/Socket/TslSocket.hpp"

#ifdef _MSC_VER
#pragma warning(disable: 4127) // "conditional expression is constant" generated by the FD_SET macro
#endif


namespace {
    // Define the low-level send/receive flags, which depend on the OS
#ifdef SFML_SYSTEM_LINUX
    const int flags = MSG_NOSIGNAL;
#else
    const int flags = 0;
#endif
}

namespace ssf {
    TslSocket::TslSocket(const SocketSide &type) : Socket(Tcp) {
        meth = (type == SocketSide::Client) ? TLS_client_method() : TLS_server_method();
        ctx = SSL_CTX_new(meth);
        if (ctx == NULL) throw std::runtime_error("Failed to create ctx.");

        if (type == SocketSide::Server) {

            SSL_CTX_set_default_passwd_cb_userdata(ctx, (void*)("sadza"));

            if (SSL_CTX_use_certificate_file(ctx, "./SSL/cert.pem", SSL_FILETYPE_PEM) <= 0) {
                throw std::runtime_error("Failed to load certificate file.");
            }
            if (SSL_CTX_use_PrivateKey_file(ctx, "./SSL/key.pem", SSL_FILETYPE_PEM) <= 0) {
                throw std::runtime_error("Failed to load key file.");
            }
            if (!SSL_CTX_check_private_key(ctx)) {
                throw std::runtime_error("Private key does not match the certificate public key.");
            }
        }
    }

    TslSocket::~TslSocket() {
        SSL_shutdown(ssl);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
    }

    unsigned short TslSocket::getLocalPort() const {
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

    sf::IpAddress TslSocket::getRemoteAddress() const {
        if (getHandle() != priv::SocketImpl::invalidSocket()) {
            // Retrieve informations about the remote end of the socket
            sockaddr_in address;
            priv::SocketImpl::AddrLength size = sizeof(address);
            if (getpeername(getHandle(), reinterpret_cast<sockaddr *>(&address), &size) != -1) {
                return sf::IpAddress(ntohl(address.sin_addr.s_addr));
            }
        }

        // We failed to retrieve the address
        return sf::IpAddress::None;
    }

    unsigned short TslSocket::getRemotePort() const {
        if (getHandle() != priv::SocketImpl::invalidSocket()) {
            // Retrieve informations about the remote end of the socket
            sockaddr_in address;
            priv::SocketImpl::AddrLength size = sizeof(address);
            if (getpeername(getHandle(), reinterpret_cast<sockaddr *>(&address), &size) != -1) {
                return ntohs(address.sin_port);
            }
        }

        // We failed to retrieve the port
        return 0;
    }

    Socket::Status TslSocket::connect(const sf::IpAddress &remoteAddress, unsigned short remotePort, sf::Time timeout) {
        Socket::Status returnStatus;
        // Disconnect the socket if it is already connected
        disconnect();

        // Create the internal socket if it doesn't exist
        create();

        // Create the remote address
        sockaddr_in address = priv::SocketImpl::createAddress(remoteAddress.toInteger(), remotePort);

        if (timeout <= sf::Time::Zero) {
            // ----- We're not using a timeout: just try to connect -----

            // Connect the socket
            if (::connect(getHandle(), reinterpret_cast<sockaddr *>(&address), sizeof(address)) == -1)
                returnStatus = priv::SocketImpl::getErrorStatus();
                // Connection succeeded
            else
                returnStatus = Done;
        }
        else
        {
            // ----- We're using a timeout: we'll need a few tricks to make it work -----

            // Save the previous blocking state
            bool blocking = isBlocking();

            // Switch to non-blocking to enable our connection timeout
            if (blocking)
                setBlocking(false);

            // Try to connect to the remote address
            if (::connect(getHandle(), reinterpret_cast<sockaddr *>(&address), sizeof(address)) >= 0) {
                // We got instantly connected! (it may no happen a lot...)
                setBlocking(blocking);
                return Done;
            }

            // Get the error status
            Status status = priv::SocketImpl::getErrorStatus();

            // If we were in non-blocking mode, return immediately
            if (!blocking)
                return status;

            // Otherwise, wait until something happens to our socket (success, timeout or error)
            if (status == Socket::NotReady) {
                // Setup the selector
                fd_set selector;
                FD_ZERO(&selector);
                FD_SET(getHandle(), &selector);

                // Setup the timeout
                timeval time;
                time.tv_sec = static_cast<long>(timeout.asMicroseconds() / 1000000);
                time.tv_usec = static_cast<long>(timeout.asMicroseconds() % 1000000);

                // Wait for something to write on our socket (which means that the connection request has returned)
                if (select(static_cast<int>(getHandle() + 1), NULL, &selector, NULL, &time) > 0) {
                    // At this point the connection may have been either accepted or refused.
                    // To know whether it's a success or a failure, we must check the address of the connected peer
                    if (getRemoteAddress() != sf::IpAddress::None) {
                        // Connection accepted
                        status = Done;
                    } else {
                        // Connection refused
                        status = priv::SocketImpl::getErrorStatus();
                    }
                } else {
                    // Failed to connect before timeout is over
                    status = priv::SocketImpl::getErrorStatus();
                }
            }

            // Switch back to blocking mode
            setBlocking(true);

            returnStatus = status;
        }

        // Now we have TCP conncetion. Start SSL negotiation.
        if (returnStatus == Done) {
            ssl = SSL_new(ctx);
            if (ssl == NULL) throw std::runtime_error("Failed to create ssl.");

            SSL_set_fd(ssl, getHandle());
            if (SSL_connect(ssl) == -1) throw std::runtime_error("Failed SSL_connect");

            X509 *server_cert = SSL_get_peer_certificate(ssl);
            if (server_cert == NULL) throw std::runtime_error("Invalid server cert.");

            char * str;
            str = X509_NAME_oneline(X509_get_subject_name(server_cert), 0, 0);
            printf("\t Subject: %s\n", str);
            OPENSSL_free (str);

            str = X509_NAME_oneline(X509_get_issuer_name(server_cert), 0, 0);
            printf("\t Issuer: %s\n", str);
            OPENSSL_free (str);

            X509_free(server_cert);
        }

        return returnStatus;
    }

    void TslSocket::disconnect() {
        // Close the socket
        close();

        // Reset the pending packet data
        m_pendingPacket = PendingPacket();
    }

    Socket::Status TslSocket::send(const void *data, std::size_t size) {
        if (!isBlocking())
            SysLog::Print(SysLog::Severity::Warning, "TslSocket: Partial sends might not be handled properly.");

        std::size_t sent;

        return send(data, size, sent);
    }

    Socket::Status TslSocket::send(const void *data, std::size_t size, std::size_t &sent) {
        // Check the parameters
        if (!data || (size == 0)) {
            SysLog::Print(SysLog::Severity::Error, "TslSocket: Cannot send data over the network (no data to send)");
            return Error;
        }

        // Loop until every byte has been sent
        int result = 0;
        for (sent = 0; sent < size; sent += result) {
            // Send a chunk of data
            result = SSL_write(ssl, static_cast<const char *>(data) + sent, static_cast<int>(size - sent));
            //result = ::send(getHandle(), static_cast<const char *>(data) + sent, static_cast<int>(size - sent), flags);

            // Check for errors
            if (result < 0) {
                Status status = priv::SocketImpl::getErrorStatus();

                if ((status == NotReady) && sent)
                    return Partial;

                return status;
            }
        }

        return Done;
    }

    Socket::Status TslSocket::receive(void *data, std::size_t size, std::size_t &received) {
        // First clear the variables to fill
        received = 0;

        // Check the destination buffer
        if (!data) {
            SysLog::Print(SysLog::Severity::Error, "Cannot receive data from the network (the destination buffer is invalid)");
            return Error;
        }

        // Receive a chunk of bytes

        int sizeReceived = SSL_read(ssl, static_cast<char *>(data), static_cast<int>(size));
        //int sizeReceived = recv(getHandle(), static_cast<char *>(data), static_cast<int>(size), flags);

        // Check the number of bytes received
        if (sizeReceived > 0) {
            received = static_cast<std::size_t>(sizeReceived);
            return Done;
        } else if (sizeReceived == 0) {
            return Socket::Disconnected;
        } else {
            return priv::SocketImpl::getErrorStatus();
        }
    }

    Socket::Status TslSocket::send(sf::Packet &packet) {
        std::size_t size = 0;
        const void *data = packet.onSend(size);

        // First convert the packet size to network byte order
        sf::Uint32 packetSize = htonl(static_cast<sf::Uint32>(size));

        // Allocate memory for the data block to send
        std::vector<char> blockToSend(sizeof(packetSize) + size);

        // Copy the packet size and data into the block to send
        std::memcpy(&blockToSend[0], &packetSize, sizeof(packetSize));
        if (size > 0)
            std::memcpy(&blockToSend[0] + sizeof(packetSize), data, size);

        // Send the data block
        std::size_t sent;
        Status status = send(&blockToSend[0] + packet.m_sendPos, blockToSend.size() - packet.m_sendPos, sent);

        // In the case of a partial send, record the location to resume from
        if (status == Partial) {
            packet.m_sendPos += sent;
        } else if (status == Done) {
            packet.m_sendPos = 0;
        }

        return status;
    }

    Socket::Status TslSocket::receive(sf::Packet &packet) {
        // First clear the variables to fill
        packet.clear();

        // We start by getting the size of the incoming packet
        sf::Uint32 packetSize = 0;
        std::size_t received = 0;
        if (m_pendingPacket.SizeReceived < sizeof(m_pendingPacket.Size)) {
            // Loop until we've received the entire size of the packet
            // (even a 4 byte variable may be received in more than one call)
            while (m_pendingPacket.SizeReceived < sizeof(m_pendingPacket.Size)) {
                char *data = reinterpret_cast<char *>(&m_pendingPacket.Size) + m_pendingPacket.SizeReceived;
                Status status = receive(data, sizeof(m_pendingPacket.Size) - m_pendingPacket.SizeReceived, received);
                m_pendingPacket.SizeReceived += received;

                if (status != Done)
                    return status;
            }

            // The packet size has been fully received
            packetSize = ntohl(m_pendingPacket.Size);
        } else {
            // The packet size has already been received in a previous call
            packetSize = ntohl(m_pendingPacket.Size);
        }

        // Loop until we receive all the packet data
        char buffer[1024];
        while (m_pendingPacket.Data.size() < packetSize) {
            // Receive a chunk of data
            std::size_t sizeToGet = std::min(static_cast<std::size_t>(packetSize - m_pendingPacket.Data.size()),
                                             sizeof(buffer));
            Status status = receive(buffer, sizeToGet, received);
            if (status != Done)
                return status;

            // Append it into the packet
            if (received > 0) {
                m_pendingPacket.Data.resize(m_pendingPacket.Data.size() + received);
                char *begin = &m_pendingPacket.Data[0] + m_pendingPacket.Data.size() - received;
                std::memcpy(begin, buffer, received);
            }
        }

        // We have received all the packet data: we can copy it to the user packet
        if (!m_pendingPacket.Data.empty())
            packet.onReceive(&m_pendingPacket.Data[0], m_pendingPacket.Data.size());

        // Clear the pending packet data
        m_pendingPacket = PendingPacket();

        return Done;
    }

    TslSocket::PendingPacket::PendingPacket() :
            Size(0),
            SizeReceived(0),
            Data() {

    }
}

