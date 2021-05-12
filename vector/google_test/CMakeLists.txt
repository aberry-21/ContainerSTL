cmake_minimum_required(VERSION 3.13)

project(vector_test VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(
#        -Werror
#        -Wall
#        -Wextra
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

# gTest ------------------------------------------------------------------------

# This module enables populating content at configure time
include(FetchContent)
FetchContent_Declare(gtest
        QUIET
        URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
        )
FetchContent_MakeAvailable(gtest)

# ------------------------------------------------------------------------------


add_executable(${PROJECT_NAME} src/test.cpp includes/A.h)

target_include_directories(${PROJECT_NAME} PUBLIC ../ , ../../ , .)
target_link_libraries(${PROJECT_NAME} PUBLIC gtest gtest_main)
