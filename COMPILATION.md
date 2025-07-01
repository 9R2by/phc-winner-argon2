cc -std=c17 -O3 -Wall -g -Iinclude -Isrc -pthread -march=native  src/argon2.c src/core.c src/blake2/blake2b.c src/thread.c src/encoding.c src/opt.c src/run.c -o argon2

cc -std=c17 -O3 -Wall -g -Iinclude -Isrc -pthread -march=native  -Wextra -Wno-type-limits src/argon2.c src/core.c src/blake2/blake2b.c src/thread.c src/encoding.c src/opt.c src/test.c -o testcase
