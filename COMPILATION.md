cc -std=c17 -O3 -Wall -g -Iinclude -Isrc -pthread -march=native  src/argon2.c src/core.c src/blake2/blake2b.c src/thread.c src/encoding.c src/opt.c src/run.c -o argon2
cc -std=c17 -O3 -Wall -g -Iinclude -Isrc -pthread -march=native  -Wextra -Wno-type-limits src/argon2.c src/core.c src/blake2/blake2b.c src/thread.c src/encoding.c src/opt.c src/test.c -o testcase

gcc -std=c17 -O3 -Wall -g -Iinclude -Isrc -pthread -march=native  src/argon2.c src/core.c src/blake2/blake2b.c src/thread.c src/encoding.c src/opt.c src/run.c -o argon2
gcc -std=c17 -O3 -Wall -g -Iinclude -Isrc -pthread -march=native  -Wextra -Wno-type-limits src/argon2.c src/core.c src/blake2/blake2b.c src/thread.c src/encoding.c src/opt.c src/test.c -o testcase


clang -std=c17 -O3 -Wall -Iinclude -Isrc -pthread -march=native  -Wextra -Wno-type-limits src/argon2.c src/core.c src/blake2/blake2b.c src/thread.c src/encoding.c src/opt.c src/run.c -o argon2
clang -std=c17 -O3 -Wall -Iinclude -Isrc -pthread -march=native  -Wextra -Wno-type-limits src/argon2.c src/core.c src/blake2/blake2b.c src/thread.c src/encoding.c src/opt.c src/test.c -o testcase

cmake .
cmake --build .
cmake --build . --target argon2
Or:
cmake --build . --target testcase


using the wasm compiler:

emcc -std=c17 -O3 -Wall -msimd128 -msse2 -Iinclude -Isrc -pthread -Wextra -Wno-type-limits src/argon2.c src/core.c src/blake2/blake2b.c src/thread.c src/encoding.c src/opt.c src/test.c -o testcase