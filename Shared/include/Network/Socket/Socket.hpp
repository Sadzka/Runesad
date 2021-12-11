#ifndef SADZA_CLIENT_SOCKET_HPP
#define SADZA_CLIENT_SOCKET_HPP

#include "Utils/NonCopyable.hpp"
#include "SocketHandle.hpp"
#include <iostream>

namespace sf {
    using Port = unsigned short;
}

namespace ssf {

    enum class SocketSide {
        Client,
        Server
    };

    class SocketSelector;

    class Socket : NonCopyable {
    public:

        enum Status {
            Done,         //!< The socket has sent / received the data
            NotReady,     //!< The socket is not ready to send / receive data yet
            Partial,      //!< The socket sent a part of the data
            Disconnected, //!< The TCP socket has been disconnected
            Error         //!< An unexpected error happened
        };

        enum {
            AnyPort = 0 //!< Special value that tells the system to pick any available port
        };

    public:

        virtual ~Socket();

        void setBlocking(bool blocking);

        bool isBlocking() const;

    protected:

        enum Type {
            Tcp, //!< TCP protocol
            Udp  //!< UDP protocol
        };

        Socket(Type type);

        SocketHandle getHandle() const;

        void create();

        void create(SocketHandle handle);

        void close();

    private:

        friend class SocketSelector;

        Type m_type;       //!< Type of the socket (TCP or UDP)
        SocketHandle m_socket;     //!< Socket descriptor
        bool m_isBlocking; //!< Current blocking mode of the socket
    };

}

#endif //SADZA_CLIENT_SOCKET_HPP
