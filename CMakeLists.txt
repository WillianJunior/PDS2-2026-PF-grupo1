cmake_minimum_required(VERSION 3.21)
cmake_policy(SET CMP0135 NEW)

project(edu_social_backend VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)

option(ENABLE_COVERAGE "Enable coverage instrumentation (GCC/Clang only)" ON)

find_package(Threads REQUIRED)

function(set_runtime_output_to_bin target)
    set_target_properties(
        ${target}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )

    foreach(CONFIG_TYPE Debug Release RelWithDebInfo MinSizeRel)
        string(TOUPPER ${CONFIG_TYPE} CONFIG_TYPE_UPPER)
        set_target_properties(
            ${target}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_${CONFIG_TYPE_UPPER} ${CMAKE_BINARY_DIR}/bin
        )
    endforeach()
endfunction()

function(set_project_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endfunction()

function(enable_coverage target)
    if(ENABLE_COVERAGE AND NOT MSVC)
        target_compile_options(${target} PUBLIC --coverage)
        target_link_options(${target} PUBLIC --coverage)
    endif()
endfunction()

file(GLOB CORE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/domain/*.cpp
)

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
)

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

enable_coverage(edu_social_core)
set_project_warnings(edu_social_core)

add_executable(edu_social_backend src/main.cpp)

target_link_libraries(
    edu_social_backend
    PRIVATE
    edu_social_core
)

set_project_warnings(edu_social_backend)
set_runtime_output_to_bin(edu_social_backend)

add_executable(count_commits_alunos scripts/count_commits_alunos.cpp)

if(MSVC)
    target_compile_options(count_commits_alunos PRIVATE /W4 /permissive- /utf-8)
else()
    target_compile_options(count_commits_alunos PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_runtime_output_to_bin(count_commits_alunos)

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
        edu_social_core
        Threads::Threads
    )

    enable_coverage(edu_social_tests)
    set_project_warnings(edu_social_tests)
    set_runtime_output_to_bin(edu_social_tests)

    add_test(NAME edu_social_tests COMMAND edu_social_tests)
endif()
