file(GLOB_RECURSE CLIENT_SOURCES ${PROJECT_SOURCE_DIR}/Client/*.cpp)

add_executable(Client ${CLIENT_SOURCES})
target_compile_definitions(Client PUBLIC _CLIENT_)

target_link_libraries(Client
        Shared
        sfml-window sfml-graphics sfml-audio
        tgui
        )

include_directories(
        ${PROJECT_SOURCE_DIR}/Client/include/
        ${TGUI_INCLUDE_DIR}
)

