cmake_minimum_required(VERSION 3.25.1)
project(argon2 C)

set(CMAKE_C_STANDARD 23)



set(ARGON_2_SOURCES
        src/argon2.c
        src/core.c
        src/blake2/blake2b.c
        src/thread.c
        src/encoding.c
        src/opt.c
        src/run.c
)




add_executable(argon2 ${ARGON_2_SOURCES} ${HEADERS})

target_include_directories(argon2 PRIVATE include)

target_compile_options(argon2 PRIVATE
        -O3
        -Wall
        -Wextra
        -Wno-type-limits
        -march=native
        -g
        -pthread
)

find_package(Threads REQUIRED)
target_link_libraries(argon2 PRIVATE Threads::Threads)


add_executable(testcase
        src/argon2.c
        src/core.c
        src/blake2/blake2b.c
        src/thread.c
        src/encoding.c
        src/opt.c
        src/test.c
)

# Include directories for headers
target_include_directories(testcase PRIVATE include src)

# Match the compile flags used in your clang command
target_compile_options(testcase PRIVATE
        -std=c17
        -O3
        -Wall
        -Wextra
        -Wno-type-limits
        -march=native
        -pthread
)

# Link with threads
find_package(Threads REQUIRED)
target_link_libraries(testcase PRIVATE Threads::Threads)

# Optional: add a 'make test' equivalent
add_custom_target(test
        COMMAND testcase
        DEPENDS testcase
        COMMENT "Running Argon2 testcases"
)