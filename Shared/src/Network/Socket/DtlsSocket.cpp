#include "Network/Socket/DtlsSocket.hpp"

#include "Sys/SysLog.hpp"


namespace ssf {
    Socket::Status DtlsSocket::connect(const sf::IpAddress &remoteAddress, unsigned short remotePort, sf::Time timeout) {
        Socket::Status returnStatus;

        // Create the internal socket if it doesn't exist
        create();

        // Create the remote address
        sockaddr_in address = priv::SocketImpl::createAddress(remoteAddress.toInteger(), remotePort);

        // Bind socket to address
        if (::bind(getHandle(), reinterpret_cast<sockaddr *>(&address), sizeof(address)) == -1) {
            std::cerr << "Failed to bind Dtls socket to  " <<  remoteAddress.toString() <<":"<< remotePort << std::endl;
            return Error;
        }
        //sockaddr_in address = priv::SocketImpl::createAddress(remoteAddress.toInteger(), remotePort);

        if (timeout <= sf::Time::Zero) {
            // ----- We're not using a timeout: just try to connect -----

            // Connect the socket
            if (::connect(getHandle(), reinterpret_cast<sockaddr *>(&address), sizeof(address)) == -1)
                returnStatus = priv::SocketImpl::getErrorStatus();
                // Connection succeeded
            else
                returnStatus = Done;
        }

        // Now we have TCP conncetion. Start SSL negotiation.
        printf("status: %d %d", returnStatus, Done);
        if (returnStatus == Done) {
            ssl = SSL_new(ctx);
            if (ssl == NULL) throw std::runtime_error("Failed to create ssl.");

            int retval = SSL_connect(ssl);
            if (retval <= 0) {

                int ssl_error = SSL_get_verify_result(ssl);
                printf("dd %d\n", ssl_error);

                switch (SSL_get_error(ssl, retval)) {
                    case SSL_ERROR_ZERO_RETURN:
                        fprintf(stderr, "SSL_connect failed with SSL_ERROR_ZERO_RETURN\n");
                        break;
                    case SSL_ERROR_WANT_READ:
                        fprintf(stderr, "SSL_connect failed with SSL_ERROR_WANT_READ\n");
                        break;
                    case SSL_ERROR_WANT_WRITE:
                        fprintf(stderr, "SSL_connect failed with SSL_ERROR_WANT_WRITE\n");
                        break;
                    case SSL_ERROR_WANT_CONNECT:
                        fprintf(stderr, "SSL_connect failed with SSL_ERROR_WANT_CONNECT\n");
                        break;
                    case SSL_ERROR_WANT_ACCEPT:
                        fprintf(stderr, "SSL_connect failed with SSL_ERROR_WANT_ACCEPT\n");
                        break;
                    case SSL_ERROR_WANT_X509_LOOKUP:
                        fprintf(stderr, "SSL_connect failed with SSL_ERROR_WANT_X509_LOOKUP\n");
                        break;
                    case SSL_ERROR_SYSCALL:
                        fprintf(stderr, "SSL_connect failed with SSL_ERROR_SYSCALL\n");
                        break;
                    case SSL_ERROR_SSL:
                        fprintf(stderr, "SSL_connect failed with SSL_ERROR_SSL\n");
                        break;
                    default:
                        fprintf(stderr, "SSL_connect failed with unknown error\n");
                        break;
                }
                exit(EXIT_FAILURE);
            }

        }

        return returnStatus;
    }

    DtlsSocket::DtlsSocket(const SocketSide &type) : Socket(Udp), m_buffer(MaxDatagramSize) {
        meth = (type == SocketSide::Client) ? DTLS_client_method() : DTLS_server_method();
        ctx = SSL_CTX_new(meth);
        if (ctx == NULL) throw std::runtime_error("Failed to create ctx.");
        if (type == SocketSide::Server) {

            SSL_CTX_set_default_passwd_cb_userdata(ctx, (void *) ("sadza"));

            if (SSL_CTX_use_certificate_file(ctx, "./SSL/cert.pem", SSL_FILETYPE_PEM) <= 0) {
                throw std::runtime_error("Failed to load certificate file.");
            }
            if (SSL_CTX_use_PrivateKey_file(ctx, "./SSL/key.pem", SSL_FILETYPE_PEM) <= 0) {
                throw std::runtime_error("Failed to load key file.");
            }
            if (!SSL_CTX_check_private_key(ctx)) {
                throw std::runtime_error("Private key does not match the certificate public key.");
            }
        } else {
//            SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, [](){});
//            SSL_CTX_set_cookie_generate_cb(ctx, generate_cookie);
//            SSL_CTX_set_cookie_verify_cb(ctx, verify_cookie);
        }
        if (type == SocketSide::Server) {
            SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, [](int ok, X509_STORE_CTX *store) {
                char data[256];

                if (!ok) {
                    X509 *cert = X509_STORE_CTX_get_current_cert(store);
                    int  depth = X509_STORE_CTX_get_error_depth(store);
                    int  err = X509_STORE_CTX_get_error(store);

                    fprintf(stderr, "-Error with certificate at depth: %i\n", depth);
                    X509_NAME_oneline(X509_get_issuer_name(cert), data, 256);
                    fprintf(stderr, "  issuer   = %s\n", data);
                    X509_NAME_oneline(X509_get_subject_name(cert), data, 256);
                    fprintf(stderr, "  subject  = %s\n", data);
                    fprintf(stderr, "  err %i:%s\n", err, X509_verify_cert_error_string(err));
                }

                return ok;
            });
        }

    }

    DtlsSocket::~DtlsSocket() {
        SSL_shutdown(ssl);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
    }

    unsigned short DtlsSocket::getLocalPort() const {
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

    Socket::Status DtlsSocket::bind(unsigned short port, const sf::IpAddress &address) {
        // Close the socket if it is already bound
        close();

        // Create the internal socket if it doesn't exist
        create();

        // Check if the address is valid
        if ((address == sf::IpAddress::None) || (address == sf::IpAddress::Broadcast))
            return Error;

        // Bind the socket
        sockaddr_in addr = priv::SocketImpl::createAddress(address.toInteger(), port);
        if (::bind(getHandle(), reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) == -1) {
            SysLog::Print(SysLog::Severity::Error, "Failed to bind socket to port %d", port);
            return Error;
        }
        ssl = SSL_new(ctx);
        if (ssl == NULL) throw std::runtime_error("Failed to create ssl.");
        if (SSL_connect(ssl) == -1) throw std::runtime_error("Failed SSL_connect");

        return Done;
    }

    void DtlsSocket::unbind() {
        // Simply close the socket
        close();
    }

    Socket::Status
    DtlsSocket::send(const void *data, std::size_t size, const sf::IpAddress &remoteAddress,
                     unsigned short remotePort) {
        // Create the internal socket if it doesn't exist
        create();

        // Make sure that all the data will fit in one datagram
        if (size > MaxDatagramSize) {

            SysLog::Print(SysLog::Severity::Error,
                          "Cannot send data over the network (the number of bytes to send is greater than sf::DtlsSocket::MaxDatagramSize)");
            return Error;
        }

        // Build the target address
        sockaddr_in address = priv::SocketImpl::createAddress(remoteAddress.toInteger(), remotePort);

        // Send the data (unlike TCP, all the data is always sent in one call)
        int sent = SSL_write(ssl, static_cast<const char *>(data), static_cast<int>(size));
//        int sent = sendto(getHandle(), static_cast<const char *>(data), static_cast<int>(size), 0,
//                          reinterpret_cast<sockaddr *>(&address), sizeof(address));

        // Check for errors
        if (sent < 0)
            return priv::SocketImpl::getErrorStatus();

        return Done;
    }

    Socket::Status
    DtlsSocket::receive(void *data, std::size_t size, std::size_t &received, sf::IpAddress &remoteAddress,
                        unsigned short &remotePort) {
        // First clear the variables to fill
        received = 0;
        remoteAddress = sf::IpAddress();
        remotePort = 0;

        // Check the destination buffer
        if (!data) {
            SysLog::Print(SysLog::Severity::Error,
                          "Cannot receive data from the network (the destination buffer is invalid)");
            return Error;
        }

        // Data that will be filled with the other computer's address
        //sockaddr_in address = priv::SocketImpl::createAddress(INADDR_ANY, 0);

        // Receive a chunk of bytes
        //priv::SocketImpl::AddrLength addressSize = sizeof(address);

        int sizeReceived = SSL_read(ssl, static_cast<char *>(data), static_cast<int>(size));
//        int sizeReceived = recvfrom(getHandle(), static_cast<char *>(data), static_cast<int>(size), 0,
//                                    reinterpret_cast<sockaddr *>(&address), &addressSize);

        // Check for errors
        if (sizeReceived < 0)
            return priv::SocketImpl::getErrorStatus();

        // Fill the sender informations
        received = static_cast<std::size_t>(sizeReceived);
        //remoteAddress = sf::IpAddress(ntohl(address.sin_addr.s_addr));
        //remotePort = ntohs(address.sin_port);

        return Done;
    }

    Socket::Status DtlsSocket::send(sf::Packet &packet, const sf::IpAddress &remoteAddress, unsigned short remotePort) {
        // UDP is a datagram-oriented protocol (as opposed to TCP which is a stream protocol).
        // Sending one datagram is almost safe: it may be lost but if it's received, then its data
        // is guaranteed to be ok. However, splitting a packet into multiple datagrams would be highly
        // unreliable, since datagrams may be reordered, dropped or mixed between different sources.
        // That's why SFML imposes a limit on packet size so that they can be sent in a single datagram.
        // This also removes the overhead associated to packets -- there's no size to send in addition
        // to the packet's data.

        // Get the data to send from the packet
        std::size_t size = 0;
        const void *data = packet.onSend(size);

        // Send it
        return send(data, size, remoteAddress, remotePort);
    }

    Socket::Status DtlsSocket::receive(sf::Packet &packet, sf::IpAddress &remoteAddress, unsigned short &remotePort) {
        // See the detailed comment in send(Packet) above.

        // Receive the datagram
        std::size_t received = 0;
        Status status = receive(&m_buffer[0], m_buffer.size(), received, remoteAddress, remotePort);

        // If we received valid data, we can copy it to the user packet
        packet.clear();
        if ((status == Done) && (received > 0))
            packet.onReceive(&m_buffer[0], received);

        return status;
    }


} // namespace ssf