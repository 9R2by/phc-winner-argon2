cmake_minimum_required(VERSION 3.31)
project(argon2 C)

set(CMAKE_C_STANDARD 23)

target_compile_options(argon2 PRIVATE
        -O3
        -Wall
        -Wextra
        -Wno-type-limits
        -march=native
        -g
        -pthread
)

set(ARGON_2_SOURCES
        src/argon2.c
        src/core.c
        src/blake2/blake2b.c
        src/thread.c
        src/encoding.c
        src/opt.c
        src/run.c
)

add_executable(argon2 ${ARGON_2_SOURCES})
