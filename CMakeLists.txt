cmake_minimum_required(VERSION 3.13)

project(ft_containers VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(
#    -Werror
#    -Wall
#    -Wextra
)

include(FetchContent)
FetchContent_Declare(gtest
    QUIET
    URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
    )
FetchContent_MakeAvailable(gtest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

add_executable(${PROJECT_NAME} vector/google_test/src/test.cpp tools/memory.h tools/exception.h tools/profile.h
                                main.cc vector/vector.h vector/random_access_iterator.h tools/utility.h tools/reverse_iterator.h)

target_include_directories(${PROJECT_NAME} PUBLIC .)
target_link_libraries(${PROJECT_NAME} PUBLIC gtest gtest_main)
