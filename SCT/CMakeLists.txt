file(GLOB_RECURSE SCT_SOURCES ${PROJECT_SOURCE_DIR}/SCT/*.cpp)

add_executable(SCT ${SCT_SOURCES})

set(RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/SCT/Server/bin/)

target_compile_definitions(SCT PUBLIC _SCT_)

target_link_libraries(SCT
        Shared
        sfml-system sfml-network
)

include_directories(
        ${PROJECT_SOURCE_DIR}/SCT/Server
)

set_target_properties( SCT
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/SCT/Server/bin/"
)
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/SCT/Server/bin/")