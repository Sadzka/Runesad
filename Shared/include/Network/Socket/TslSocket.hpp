#ifndef SADZA_CLIENT_SSLSOCKET_HPP
#define SADZA_CLIENT_SSLSOCKET_HPP

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/System/Time.hpp>
#include <algorithm>
#include <vector>

#include <openssl/rsa.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "Network/Socket/SocketImpl.hpp"
#include "Network/Socket/Socket.hpp"
#include "Sys/SysLog.hpp"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class TcpListener;

namespace ssf {
////////////////////////////////////////////////////////////
/// \brief Specialized socket using the TCP protocol
///
////////////////////////////////////////////////////////////
    class TslSocket : public Socket {
        friend class TslListener;

    public:

        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        ////////////////////////////////////////////////////////////
        TslSocket(const SocketSide &type);

        ~TslSocket();

        ////////////////////////////////////////////////////////////
        /// \brief Get the port to which the socket is bound locally
        ///
        /// If the socket is not connected, this function returns 0.
        ///
        /// \return Port to which the socket is bound
        ///
        /// \see connect, getRemotePort
        ///
        ////////////////////////////////////////////////////////////
        unsigned short getLocalPort() const;

        ////////////////////////////////////////////////////////////
        /// \brief Get the address of the connected peer
        ///
        /// If the socket is not connected, this function returns
        /// sf::IpAddress::None.
        ///
        /// \return Address of the remote peer
        ///
        /// \see getRemotePort
        ///
        ////////////////////////////////////////////////////////////
        sf::IpAddress getRemoteAddress() const;

        ////////////////////////////////////////////////////////////
        /// \brief Get the port of the connected peer to which
        ///        the socket is connected
        ///
        /// If the socket is not connected, this function returns 0.
        ///
        /// \return Remote port to which the socket is connected
        ///
        /// \see getRemoteAddress
        ///
        ////////////////////////////////////////////////////////////
        unsigned short getRemotePort() const;

        ////////////////////////////////////////////////////////////
        /// \brief Connect the socket to a remote peer
        ///
        /// In blocking mode, this function may take a while, especially
        /// if the remote peer is not reachable. The last parameter allows
        /// you to stop trying to connect after a given timeout.
        /// If the socket is already connected, the connection is
        /// forcibly disconnected before attempting to connect again.
        ///
        /// \param remoteAddress Address of the remote peer
        /// \param remotePort    Port of the remote peer
        /// \param timeout       Optional maximum time to wait
        ///
        /// \return Status code
        ///
        /// \see disconnect
        ///
        ////////////////////////////////////////////////////////////
        Status
        connect(const sf::IpAddress &remoteAddress, unsigned short remotePort, sf::Time timeout = sf::Time::Zero);

        ////////////////////////////////////////////////////////////
        /// \brief Disconnect the socket from its remote peer
        ///
        /// This function gracefully closes the connection. If the
        /// socket is not connected, this function has no effect.
        ///
        /// \see connect
        ///
        ////////////////////////////////////////////////////////////
        void disconnect();

        ////////////////////////////////////////////////////////////
        /// \brief Send raw data to the remote peer
        ///
        /// To be able to handle partial sends over non-blocking
        /// sockets, use the send(const void*, std::size_t, std::size_t&)
        /// overload instead.
        /// This function will fail if the socket is not connected.
        ///
        /// \param data Pointer to the sequence of bytes to send
        /// \param size Number of bytes to send
        ///
        /// \return Status code
        ///
        /// \see receive
        ///
        ////////////////////////////////////////////////////////////
        Status send(const void *data, std::size_t size);

        ////////////////////////////////////////////////////////////
        /// \brief Send raw data to the remote peer
        ///
        /// This function will fail if the socket is not connected.
        ///
        /// \param data Pointer to the sequence of bytes to send
        /// \param size Number of bytes to send
        /// \param sent The number of bytes sent will be written here
        ///
        /// \return Status code
        ///
        /// \see receive
        ///
        ////////////////////////////////////////////////////////////
        Status send(const void *data, std::size_t size, std::size_t &sent);

        ////////////////////////////////////////////////////////////
        /// \brief Receive raw data from the remote peer
        ///
        /// In blocking mode, this function will wait until some
        /// bytes are actually received.
        /// This function will fail if the socket is not connected.
        ///
        /// \param data     Pointer to the array to fill with the received bytes
        /// \param size     Maximum number of bytes that can be received
        /// \param received This variable is filled with the actual number of bytes received
        ///
        /// \return Status code
        ///
        /// \see send
        ///
        ////////////////////////////////////////////////////////////
        Status receive(void *data, std::size_t size, std::size_t &received);

        ////////////////////////////////////////////////////////////
        /// \brief Send a formatted packet of data to the remote peer
        ///
        /// In non-blocking mode, if this function returns sf::Socket::Partial,
        /// you \em must retry sending the same unmodified packet before sending
        /// anything else in order to guarantee the packet arrives at the remote
        /// peer uncorrupted.
        /// This function will fail if the socket is not connected.
        ///
        /// \param packet sf::Packet to send
        ///
        /// \return Status code
        ///
        /// \see receive
        ///
        ////////////////////////////////////////////////////////////
        Status send(sf::Packet &packet);

        ////////////////////////////////////////////////////////////
        /// \brief Receive a formatted packet of data from the remote peer
        ///
        /// In blocking mode, this function will wait until the whole packet
        /// has been received.
        /// This function will fail if the socket is not connected.
        ///
        /// \param packet sf::Packet to fill with the received data
        ///
        /// \return Status code
        ///
        /// \see send
        ///
        ////////////////////////////////////////////////////////////
        Status receive(sf::Packet &packet);

        ////////////////////////////////////////////////////////////
        /// \brief Send a message to the remote peer
        ///
        /// In non-blocking mode, if this function returns sf::Socket::Partial,
        /// you \em must retry sending the same unmodified packet before sending
        /// anything else in order to guarantee the packet arrives at the remote
        /// peer uncorrupted.
        /// This function will fail if the socket is not connected.
        ///
        /// \param packet sf::Packet to send
        ///
        /// \return Status code
        ///
        /// \see receive
        ///
        ////////////////////////////////////////////////////////////
        template<class T>
        Status send(const T &msg) {
            printf("Sending msg: %#010x\n", T::id);
            sf::Packet packet;
            packet << msg.id;
            packet << msg;
            return send(packet);
        }

    private:
        ////////////////////////////////////////////////////////////
        /// \brief Structure holding the data of a pending packet
        ///
        ////////////////////////////////////////////////////////////
        struct PendingPacket {
            PendingPacket();

            sf::Uint32 Size;         //!< Data of packet size
            std::size_t SizeReceived; //!< Number of size bytes received so far
            std::vector<char> Data;         //!< Data of the packet
        };

        const SSL_METHOD *meth;
        SSL_CTX *ctx;
        SSL *ssl;

        PendingPacket m_pendingPacket; //!< Temporary data of the packet currently being received
    };

}

#endif //SADZA_CLIENT_SSLSOCKET_HPP
