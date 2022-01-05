cmake_minimum_required(VERSION 3.16)
project(Runesad)

set(CMAKE_CXX_STANDARD 20)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    add_compile_definitions(DEBUG)
else()
    add_compile_definitions(RELEASE)
endif()

include(Shared/CMakeLists.txt)
include(Client/CMakeLists.txt)
include(Server/CMakeLists.txt)
include(SCT/CMakeLists.txt)

set(SFML_DIR "D:/Program Files/mingw-w64/SFML/lib/cmake/SFML")
find_package(SFML 2.5 REQUIRED COMPONENTS system window graphics audio network)

set(TGUI_DIR "D:/Program Files/mingw-w64/TGUI/lib/cmake/TGUI")
find_package(TGUI 0.9 REQUIRED)

find_package(OpenSSL REQUIRED)