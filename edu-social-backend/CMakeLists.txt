cmake_minimum_required(VERSION 3.21)

project(edu_social_backend VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

set(CROW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CROW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(CROW_BUILD_TOOLS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    asio
    URL https://github.com/chriskohlhoff/asio/archive/refs/tags/asio-1-30-2.tar.gz
)
FetchContent_MakeAvailable(asio)
set(ASIO_INCLUDE_DIR "${asio_SOURCE_DIR}/asio/include" CACHE PATH "Standalone Asio include directory" FORCE)

FetchContent_Declare(
    crow
    URL https://github.com/CrowCpp/Crow/archive/refs/tags/v1.2.1.tar.gz
)

FetchContent_Declare(
    sqlite_amalgamation
    URL
        https://www.sqlite.org/2026/sqlite-amalgamation-3510300.zip
        https://www.sqlite.org/2025/sqlite-amalgamation-3510300.zip
)

FetchContent_MakeAvailable(crow)
FetchContent_MakeAvailable(sqlite_amalgamation)

set(SQLITE_DIR ${sqlite_amalgamation_SOURCE_DIR})

find_package(Threads REQUIRED)

add_library(sqlite_local STATIC ${SQLITE_DIR}/sqlite3.c)
target_include_directories(sqlite_local PUBLIC ${SQLITE_DIR})
target_compile_definitions(sqlite_local PRIVATE SQLITE_THREADSAFE=1 SQLITE_OMIT_LOAD_EXTENSION)

if(MSVC)
    target_compile_definitions(sqlite_local PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(edu_social_backend ${APP_SOURCES})
target_include_directories(
    edu_social_backend
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${SQLITE_DIR}
)
target_link_libraries(edu_social_backend PRIVATE Crow::Crow sqlite_local Threads::Threads)

if(WIN32)
    target_link_libraries(edu_social_backend PRIVATE ws2_32 mswsock)
endif()

set_target_properties(edu_social_backend PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(MSVC)
    target_compile_options(edu_social_backend PRIVATE /W4 /permissive-)
else()
    target_compile_options(edu_social_backend PRIVATE -Wall -Wextra -Wpedantic)
endif()

foreach(CONFIG_TYPE Debug Release RelWithDebInfo MinSizeRel)
    string(TOUPPER ${CONFIG_TYPE} CONFIG_TYPE_UPPER)
    set_target_properties(
        edu_social_backend
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} ${CMAKE_BINARY_DIR}/bin
    )
endforeach()
