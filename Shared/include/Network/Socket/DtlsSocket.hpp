#ifndef SADZA_DTLSSOCKET_HPP
#define SADZA_DTLSSOCKET_HPP

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>

#include <vector>

#include <openssl/rsa.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

#include "Network/Socket/SocketImpl.hpp"
#include "Network/Socket/Socket.hpp"

////////////////////////////////////////////////////////////
/// \brief Specialized socket using the UDP protocol
///
////////////////////////////////////////////////////////////

namespace ssf {

    class DtlsSocket : public ssf::Socket {
        friend class DtlsListener;

    public:

        ////////////////////////////////////////////////////////////
        // Constants
        ////////////////////////////////////////////////////////////
        enum {
            MaxDatagramSize = 65507 //!< The maximum number of bytes that can be sent in a single UDP datagram
        };

        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        ////////////////////////////////////////////////////////////
        DtlsSocket(const SocketSide &type);

        ~DtlsSocket();
        Status connect(const sf::IpAddress &remoteAddress, unsigned short remotePort, sf::Time timeout = sf::Time::Zero);

        ////////////////////////////////////////////////////////////
        /// \brief Get the port to which the socket is bound locally
        ///
        /// If the socket is not bound to a port, this function
        /// returns 0.
        ///
        /// \return Port to which the socket is bound
        ///
        /// \see bind
        ///
        ////////////////////////////////////////////////////////////
        unsigned short getLocalPort() const;

        ////////////////////////////////////////////////////////////
        /// \brief Bind the socket to a specific port
        ///
        /// Binding the socket to a port is necessary for being
        /// able to receive data on that port.
        ///
        /// When providing sf::Socket::AnyPort as port, the listener
        /// will request an available port from the system.
        /// The chosen port can be retrieved by calling getLocalPort().
        ///
        /// Since the socket can only be bound to a single port at
        /// any given moment, if it is already bound when this
        /// function is called, it will be unbound from the previous
        /// port before being bound to the new one.
        ///
        /// \param port    Port to bind the socket to
        /// \param address Address of the interface to bind to
        ///
        /// \return Status code
        ///
        /// \see unbind, getLocalPort
        ///
        ////////////////////////////////////////////////////////////
        Status bind(unsigned short port, const sf::IpAddress &address = sf::IpAddress::Any);

        ////////////////////////////////////////////////////////////
        /// \brief Unbind the socket from the local port to which it is bound
        ///
        /// The port that the socket was previously bound to is immediately
        /// made available to the operating system after this function is called.
        /// This means that a subsequent call to bind() will be able to re-bind
        /// the port if no other process has done so in the mean time.
        /// If the socket is not bound to a port, this function has no effect.
        ///
        /// \see bind
        ///
        ////////////////////////////////////////////////////////////
        void unbind();

        ////////////////////////////////////////////////////////////
        /// \brief Send raw data to a remote peer
        ///
        /// Make sure that \a size is not greater than
        /// DtlsSocket::MaxDatagramSize, otherwise this function will
        /// fail and no data will be sent.
        ///
        /// \param data          Pointer to the sequence of bytes to send
        /// \param size          Number of bytes to send
        /// \param remoteAddress Address of the receiver
        /// \param remotePort    Port of the receiver to send the data to
        ///
        /// \return Status code
        ///
        /// \see receive
        ///
        ////////////////////////////////////////////////////////////
        Status send(const void *data, std::size_t size, const sf::IpAddress &remoteAddress, unsigned short remotePort);

        ////////////////////////////////////////////////////////////
        /// \brief Receive raw data from a remote peer
        ///
        /// In blocking mode, this function will wait until some
        /// bytes are actually received.
        /// Be careful to use a buffer which is large enough for
        /// the data that you intend to receive, if it is too small
        /// then an error will be returned and *all* the data will
        /// be lost.
        ///
        /// \param data          Pointer to the array to fill with the received bytes
        /// \param size          Maximum number of bytes that can be received
        /// \param received      This variable is filled with the actual number of bytes received
        /// \param remoteAddress Address of the peer that sent the data
        /// \param remotePort    Port of the peer that sent the data
        ///
        /// \return Status code
        ///
        /// \see send
        ///
        ////////////////////////////////////////////////////////////
        Status receive(void *data, std::size_t size, std::size_t &received, sf::IpAddress &remoteAddress,
                       unsigned short &remotePort);

        ////////////////////////////////////////////////////////////
        /// \brief Send a formatted packet of data to a remote peer
        ///
        /// Make sure that the packet size is not greater than
        /// DtlsSocket::MaxDatagramSize, otherwise this function will
        /// fail and no data will be sent.
        ///
        /// \param packet        Packet to send
        /// \param remoteAddress Address of the receiver
        /// \param remotePort    Port of the receiver to send the data to
        ///
        /// \return Status code
        ///
        /// \see receive
        ///
        ////////////////////////////////////////////////////////////
        Status send(sf::Packet &packet, const sf::IpAddress &remoteAddress, unsigned short remotePort);

        ////////////////////////////////////////////////////////////
        /// \brief Receive a formatted packet of data from a remote peer
        ///
        /// In blocking mode, this function will wait until the whole packet
        /// has been received.
        ///
        /// \param packet        Packet to fill with the received data
        /// \param remoteAddress Address of the peer that sent the data
        /// \param remotePort    Port of the peer that sent the data
        ///
        /// \return Status code
        ///
        /// \see send
        ///
        ////////////////////////////////////////////////////////////
        Status receive(sf::Packet &packet, sf::IpAddress &remoteAddress, unsigned short &remotePort);

    private:

        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        std::vector<char> m_buffer; //!< Temporary buffer holding the received data in Receive(Packet)

        const SSL_METHOD *meth;
        SSL_CTX *ctx;
        SSL *ssl;
        BIO *bio;
    };

} // namespace ssf

#endif //SADZA_DTLSSOCKET_HPP
