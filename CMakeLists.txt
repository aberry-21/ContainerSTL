cmake_minimum_required(VERSION 3.13)

project(ft_containers VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(
#    -Werror
#    -Wall
#    -Wextra
)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

#aux_source_directory(tools DIR_SRCS)
add_executable(${PROJECT_NAME} tools/memory.h main.cc vector/vector.h)

target_include_directories(${PROJECT_NAME} PUBLIC .)