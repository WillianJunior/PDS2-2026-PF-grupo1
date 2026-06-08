cmake_minimum_required(VERSION 3.21)
cmake_policy(SET CMP0135 NEW)

project(edu_social_backend VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)

option(ENABLE_COVERAGE "Enable coverage instrumentation" ON)

find_package(Threads REQUIRED)

file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/domain/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/database/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/http/*.cpp
)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
)

if(CORE_SOURCES)
    add_library(edu_social_core STATIC ${CORE_SOURCES})

    target_include_directories(
        edu_social_core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/domain
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

add_executable(edu_social_backend src/main.cpp)

target_include_directories(
    edu_social_backend
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/domain
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

if(TEST_SOURCES)
    add_executable(edu_social_tests ${TEST_SOURCES})

    target_include_directories(
        edu_social_tests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/domain
        ${CMAKE_CURRENT_SOURCE_DIR}/tests
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
