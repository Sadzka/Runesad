//
// Created by Sadza on 19.08.2021.
//

#ifndef SADZA_CLIENT_DtlsListener_HPP
#define SADZA_CLIENT_DtlsListener_HPP

#include <SFML/Network/Export.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <Network/Socket/Socket.hpp>
#include <Network/Socket/DtlsSocket.hpp>


namespace ssf {
    class DtlsSocket;

////////////////////////////////////////////////////////////
/// \brief Socket that listens to new TCP connections
///
////////////////////////////////////////////////////////////
    class DtlsListener : public Socket {
    public:

        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        ////////////////////////////////////////////////////////////
        DtlsListener();

        ////////////////////////////////////////////////////////////
        /// \brief Get the port to which the socket is bound locally
        ///
        /// If the socket is not listening to a port, this function
        /// returns 0.
        ///
        /// \return Port to which the socket is bound
        ///
        /// \see listen
        ///
        ////////////////////////////////////////////////////////////
        unsigned short getLocalPort() const;

        ////////////////////////////////////////////////////////////
        /// \brief Start listening for incoming connection attempts
        ///
        /// This function makes the socket start listening on the
        /// specified port, waiting for incoming connection attempts.
        ///
        /// If the socket is already listening on a port when this
        /// function is called, it will stop listening on the old
        /// port before starting to listen on the new port.
        ///
        /// When providing sf::Socket::AnyPort as port, the listener
        /// will request an available port from the system.
        /// The chosen port can be retrieved by calling getLocalPort().
        ///
        /// \param port    Port to listen on for incoming connection attempts
        /// \param address Address of the interface to listen on
        ///
        /// \return Status code
        ///
        /// \see accept, close
        ///
        ////////////////////////////////////////////////////////////
        Status listen(unsigned short port, const sf::IpAddress &address = sf::IpAddress::Any);

        ////////////////////////////////////////////////////////////
        /// \brief Stop listening and close the socket
        ///
        /// This function gracefully stops the listener. If the
        /// socket is not listening, this function has no effect.
        ///
        /// \see listen
        ///
        ////////////////////////////////////////////////////////////
        void close();

        ////////////////////////////////////////////////////////////
        /// \brief Accept a new connection
        ///
        /// If the socket is in blocking mode, this function will
        /// not return until a connection is actually received.
        ///
        /// \param socket Socket that will hold the new connection
        ///
        /// \return Status code
        ///
        /// \see listen
        ///
        ////////////////////////////////////////////////////////////
        Status accept(DtlsSocket &socket);
    };


} // namespace ssf

#endif //SADZA_CLIENT_DtlsListener_HPP
