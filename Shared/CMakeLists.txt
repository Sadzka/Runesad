file(GLOB_RECURSE SHARED_SOURCES ${PROJECT_SOURCE_DIR}/Shared/*.cpp)

message(STATUS ${SHARED_SOURCES})
find_package(OpenSSL REQUIRED)
add_library(Shared ${SHARED_SOURCES})

target_link_libraries(Shared
        sfml-system sfml-network
        ${OPENSSL_LIBRARIES}
        ws2_32
)

include_directories(
        ${PROJECT_SOURCE_DIR}/Shared/include/
        ${OPENSSL_INCLUDE_DIR}
)