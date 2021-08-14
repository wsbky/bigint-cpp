cmake_policy(SET CMP0050 NEW)

cmake_minimum_required(VERSION 3.17)

project(Bigint-Test)

message("compiler: ${CMAKE_CXX_COMPILER}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
message("std=c++${CMAKE_CXX_STANDARD}")

set(SRC_DIR ${PROJECT_SOURCE_DIR}/)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../src)

add_compile_options(-Wall -Werror -Wextra -Wconversion -Wno-sign-conversion -Wshadow -g -O0)

enable_testing()

add_subdirectory(${PROJECT_SOURCE_DIR}/googletest)
include(GoogleTest)

add_executable(InstructionsTest ${SRC_DIR}/instructions_test.cc)
add_library(bigint STATIC ${INCLUDE_DIR}/bigint.cc)
target_include_directories(InstructionsTest PUBLIC ${INCLUDE_DIR})
target_include_directories(bigint PUBLIC ${INCLUDE_DIR})
target_link_libraries(InstructionsTest bigint gtest_main)
gtest_discover_tests(InstructionsTest)
