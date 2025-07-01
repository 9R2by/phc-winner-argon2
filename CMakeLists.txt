cmake_minimum_required(VERSION 3.31)
project(phc-winner-argon2 C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -g -Iinclude -Isrc")

add_executable(cmake_test main.c)
