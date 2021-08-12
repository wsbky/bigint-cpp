cmake_policy(SET CMP0050 NEW)

cmake_minimum_required(VERSION 3.10)

project(BigintLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -O2")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Werror -Wextra -O0 -g")

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(SAMPLE_DIR ${PROJECT_SOURCE_DIR}/sample)

add_library(bigint STATIC ${SRC_DIR}/bigint.cc)
add_executable(main ${SAMPLE_DIR}/main.cc)

target_include_directories(main PUBLIC ${SRC_DIR})
target_include_directories(bigint PUBLIC ${SRC_DIR})
target_link_libraries(main bigint)

