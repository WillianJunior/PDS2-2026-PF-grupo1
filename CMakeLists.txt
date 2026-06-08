cmake_minimum_required(VERSION 3.21)
cmake_policy(SET CMP0135 NEW)

project(edu_social_backend VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
include(CTest)

set(FETCHCONTENT_QUIET OFF)

option(ENABLE_COVERAGE "Enable coverage instrumentation" ON)

# -----------------------------------------------------------------------------
# Doctest
# -----------------------------------------------------------------------------
set(DOCTEST_SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/doctest-src")
set(DOCTEST_BINARY_DIR "${CMAKE_BINARY_DIR}/_deps/doctest-build")
set(DOCTEST_SUBBUILD_DIR "${CMAKE_BINARY_DIR}/_deps/doctest-subbuild")

if(NOT EXISTS "${DOCTEST_SOURCE_DIR}/doctest/doctest.h")
    FetchContent_Populate(
        doctest
        URL https://github.com/doctest/doctest/archive/refs/tags/v2.4.12.tar.gz
        SOURCE_DIR "${DOCTEST_SOURCE_DIR}"
        BINARY_DIR "${DOCTEST_BINARY_DIR}"
        SUBBUILD_DIR "${DOCTEST_SUBBUILD_DIR}"
    )
endif()

find_package(Threads REQUIRED)

# -----------------------------------------------------------------------------
# Coleta de fontes
# -----------------------------------------------------------------------------
file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/domain/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/database/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/http/*.cpp
)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
)

# -----------------------------------------------------------------------------
# Biblioteca principal
# -----------------------------------------------------------------------------
if(CORE_SOURCES)
    add_library(edu_social_core STATIC ${CORE_SOURCES})

    target_include_directories(
        edu_social_core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    target_link_libraries(
        edu_social_core
        PUBLIC
        Threads::Threads
    )

    if(ENABLE_COVERAGE AND NOT MSVC)
        target_compile_options(edu_social_core PUBLIC --coverage)
        target_link_options(edu_social_core PUBLIC --coverage)
    endif()

    if(MSVC)
        target_compile_options(edu_social_core PRIVATE /W4 /permissive-)
    else()
        target_compile_options(edu_social_core PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()

# -----------------------------------------------------------------------------
# Executável principal
# -----------------------------------------------------------------------------
add_executable(edu_social_backend src/main.cpp)

target_include_directories(
    edu_social_backend
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    edu_social_backend
    PRIVATE
    Threads::Threads
)

if(CORE_SOURCES)
    target_link_libraries(
        edu_social_backend
        PRIVATE
        edu_social_core
    )
endif()

if(WIN32)
    target_link_libraries(
        edu_social_backend
        PRIVATE
        ws2_32
        mswsock
    )
endif()

if(MSVC)
    target_compile_options(edu_social_backend PRIVATE /W4 /permissive-)
else()
    target_compile_options(edu_social_backend PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(
    edu_social_backend
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

foreach(CONFIG_TYPE Debug Release RelWithDebInfo MinSizeRel)
    string(TOUPPER ${CONFIG_TYPE} CONFIG_TYPE_UPPER)

    set_target_properties(
        edu_social_backend
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} ${CMAKE_BINARY_DIR}/bin
    )
endforeach()

# -----------------------------------------------------------------------------
# Testes
# -----------------------------------------------------------------------------
if(TEST_SOURCES)
    add_executable(edu_social_tests ${TEST_SOURCES})

    target_include_directories(
        edu_social_tests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${DOCTEST_SOURCE_DIR}
    )

    target_link_libraries(
        edu_social_tests
        PRIVATE
        Threads::Threads
    )

    if(CORE_SOURCES)
        target_link_libraries(
            edu_social_tests
            PRIVATE
            edu_social_core
        )
    endif()

    if(ENABLE_COVERAGE AND NOT MSVC)
        target_compile_options(edu_social_tests PRIVATE --coverage)
        target_link_options(edu_social_tests PRIVATE --coverage)
    endif()

    if(MSVC)
        target_compile_options(edu_social_tests PRIVATE /W4 /permissive-)
    else()
        target_compile_options(edu_social_tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()

    set_target_properties(
        edu_social_tests
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )

    foreach(CONFIG_TYPE Debug Release RelWithDebInfo MinSizeRel)
        string(TOUPPER ${CONFIG_TYPE} CONFIG_TYPE_UPPER)

        set_target_properties(
            edu_social_tests
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} ${CMAKE_BINARY_DIR}/bin
        )
    endforeach()

    add_test(NAME edu_social_tests COMMAND edu_social_tests)
endif()