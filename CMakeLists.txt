cmake_policy(SET CMP0050 NEW)

cmake_minimum_required(VERSION 3.10)

project(FracLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(TEST_DIR ${PROJECT_SOURCE_DIR}/test)

add_compile_options(-Wall -Werror -Wextra -O2)

add_library(Frac STATIC ${SRC_DIR}/frac.cc)
add_executable(Main ${TEST_DIR}/main.cc)

target_include_directories(Main PUBLIC ${SRC_DIR})
target_include_directories(Frac PUBLIC ${SRC_DIR})
target_link_libraries(Main Frac)

