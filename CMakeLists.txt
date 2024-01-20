##
## EPITECH PROJECT, 2023
## B-CPP-500-RUN-5-1-rtype-florian.etheve
## File description:
## CMakeLists
##

cmake_minimum_required(VERSION 3.16)

project(rtype)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

set(CMAKE_INSTALL_RPATH "$ORIGIN/lib64")

file(GLOB_RECURSE ENGINE_SOURCES "Engine/*.cpp")
file(GLOB_RECURSE CLIENT_SOURCES "Client/*.cpp")
file(GLOB_RECURSE SERVER_SOURCES "Server/*.cpp")

add_library(libEngine STATIC ${ENGINE_SOURCES})
target_include_directories(libEngine PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(libEngine sfml-system sfml-window sfml-graphics sfml-network sfml-audio nlohmann_json::nlohmann_json)

add_executable(rtype_client ${CLIENT_SOURCES})
target_include_directories(rtype_client PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(rtype_client libEngine sfml-system sfml-window sfml-graphics sfml-network sfml-audio nlohmann_json::nlohmann_json)

add_executable(rtype_server ${SERVER_SOURCES})
target_include_directories(rtype_server PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(rtype_server sfml-system sfml-window sfml-graphics sfml-network)

add_custom_command(
    TARGET rtype_client rtype_server
    POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:rtype_client>" "${CMAKE_SOURCE_DIR}"
    POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:rtype_server>" "${CMAKE_SOURCE_DIR}")

if (WIN32)
    add_custom_command(
        TARGET rtype_client rtype_server
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/build/_deps/sfml-build/lib/Debug/sfml-system-d-2.dll" "${CMAKE_SOURCE_DIR}"
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/build/_deps/sfml-build/lib/Debug/sfml-network-d-2.dll" "${CMAKE_SOURCE_DIR}"
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/build/_deps/sfml-build/lib/Debug/sfml-graphics-d-2.dll" "${CMAKE_SOURCE_DIR}"
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/build/_deps/sfml-build/lib/Debug/sfml-window-d-2.dll" "${CMAKE_SOURCE_DIR}"
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/build/_deps/sfml-build/lib/Debug/sfml-audio-d-2.dll" "${CMAKE_SOURCE_DIR}"
    )
endif()

file(GLOB JSON_FILES "Client/*.json")

include(CPack)

set(CPACK_GENERATOR_ZIP)

set(CPACK_PACKAGE_NAME "rtype")
set(CPACK_PACKAGE_VERSION "1.0")

install(TARGETS rtype_client rtype_server
    DESTINATION .
    COMPONENT Applications)

install(DIRECTORY Client/assets
    DESTINATION Client
    COMPONENT Applications)

install(FILES ${JSON_FILES}
    DESTINATION Client
    COMPONENT Applications
)
