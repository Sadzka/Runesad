#ifndef SADZA_CLIENT_SOCKETHANDLE_HPP
#define SADZA_CLIENT_SOCKETHANDLE_HPP

#include <SFML/Config.hpp>

#if defined(SFML_SYSTEM_WINDOWS)
#include <basetsd.h>
#endif

#if defined(SFML_SYSTEM_WINDOWS)
    typedef UINT_PTR SocketHandle;
#else
    typedef int SocketHandle;
#endif

#endif //SADZA_CLIENT_SOCKETHANDLE_HPP
