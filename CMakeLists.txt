cmake_minimum_required(VERSION 3.10)
project(EduSocial)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -O0 -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include include/domain tests)

file(GLOB_RECURSE ALL_SRC "src/*.cpp")
list(REMOVE_ITEM ALL_SRC "${CMAKE_SOURCE_DIR}/src/main.cpp")

add_executable(edusocial src/main.cpp ${ALL_SRC})

file(GLOB_RECURSE TEST_FILES "tests/*.cpp")
list(REMOVE_ITEM TEST_FILES "${CMAKE_SOURCE_DIR}/tests/main.cpp")

add_executable(run_tests ${TEST_FILES} ${ALL_SRC})