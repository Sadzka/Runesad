file(GLOB_RECURSE SERVER_SOURCES ${PROJECT_SOURCE_DIR}/Server/*.cpp)

add_executable(Server ${SERVER_SOURCES})

target_compile_definitions(Server PUBLIC _SERVER_)

target_link_libraries(Server
        Shared
        sfml-system sfml-network
)

include_directories(
        ${PROJECT_SOURCE_DIR}/Server/include/
)
