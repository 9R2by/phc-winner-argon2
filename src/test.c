/*
 * Argon2 reference source code package - reference C implementations
 *
 * Copyright 2015
 * Daniel Dinu, Dmitry Khovratovich, Jean-Philippe Aumasson, and Samuel Neves
 *
 * You may use this work under the terms of a Creative Commons CC0 1.0
 * License/Waiver or the Apache Public License 2.0, at your option. The terms of
 * these licenses can be found at:
 *
 * - CC0 1.0 Universal : https://creativecommons.org/publicdomain/zero/1.0
 * - Apache 2.0        : https://www.apache.org/licenses/LICENSE-2.0
 *
 * You should have received a copy of both of these licenses along with this
 * software. If not, they may be obtained at the above URLs.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "argon2.h"

#define OUT_LEN 32
#define ENCODED_LEN 108

/* Test harness will assert:
 * argon2_hash() returns ARGON2_OK
 * HEX output matches expected
 * encoded output matches expected
 * argon2_verify() correctly verifies value
 */

void hashtest(uint32_t version, uint32_t t, uint32_t m, uint32_t p, char *pwd,
              char *salt, char *hexref, char *mcfref, argon2_type type) {
    unsigned char out[OUT_LEN];
    unsigned char hex_out[OUT_LEN * 2 + 4];
    char encoded[ENCODED_LEN];
    int ret, i;

    printf("Hash test: $v=%d t=%d, m=%d, p=%d, pass=%s, salt=%s: ", version,
           t, m, p, pwd, salt);

    ret = argon2_hash(t, 1 << m, p, pwd, strlen(pwd), salt, strlen(salt), out,
                      OUT_LEN, encoded, ENCODED_LEN, type, version);
    assert(ret == ARGON2_OK);

    for (i = 0; i < OUT_LEN; ++i)
        sprintf((char *)(hex_out + i * 2), "%02x", out[i]);
    assert(memcmp(hex_out, hexref, OUT_LEN * 2) == 0);

    if (ARGON2_VERSION_NUMBER == version) {
        assert(memcmp(encoded, mcfref, strlen(mcfref)) == 0);
    }

    ret = argon2_verify(encoded, pwd, strlen(pwd), type);
    assert(ret == ARGON2_OK);
    ret = argon2_verify(mcfref, pwd, strlen(pwd), type);
    assert(ret == ARGON2_OK);

    printf("PASS\n");
}

int main() {
    int ret;
    unsigned char out[OUT_LEN];
    char const *msg;
    int version;

    version = ARGON2_VERSION_10;

    printf("Test Argon2id version number: %02x\n", version);

    /* Multiple test cases for various input values */
    hashtest(version, 2, 16, 1, "password", "somesalt",
             "09316115d5cf24ed5a15a31a3ba326e5cf32edc24702987c02b6566f61913cf7",
             "$argon2id$v=19$m=65536,t=2,p=1$c29tZXNhbHQ"
             "$CTFhFdXPJO1aFaMaO6Mm5c8y7cJHAph8ArZWb2GRPPc", Argon2_id);
    hashtest(version, 2, 18, 1, "password", "somesalt",
             "78fe1ec91fb3aa5657d72e710854e4c3d9b9198c742f9616c2f085bed95b2e8c",
             "$argon2id$v=19$m=262144,t=2,p=1$c29tZXNhbHQ"
             "$eP4eyR+zqlZX1y5xCFTkw9m5GYx0L5YWwvCFvtlbLow", Argon2_id);
    hashtest(version, 2, 8, 1, "password", "somesalt",
             "9dfeb910e80bad0311fee20f9c0e2b12c17987b4cac90c2ef54d5b3021c68bfe",
             "$argon2id$v=19$m=256,t=2,p=1$c29tZXNhbHQ"
             "$nf65EOgLrQMR/uIPnA4rEsF5h7TKyQwu9U1bMCHGi/4", Argon2_id);
    hashtest(version, 2, 8, 2, "password", "somesalt",
             "6d093c501fd5999645e0ea3bf620d7b8be7fd2db59c20d9fff9539da2bf57037",
             "$argon2id$v=19$m=256,t=2,p=2$c29tZXNhbHQ"
             "$bQk8UB/VmZZF4Oo79iDXuL5/0ttZwg2f/5U52iv1cDc", Argon2_id);
    hashtest(version, 1, 16, 1, "password", "somesalt",
             "f6a5adc1ba723dddef9b5ac1d464e180fcd9dffc9d1cbf76cca2fed795d9ca98",
             "$argon2id$v=19$m=65536,t=1,p=1$c29tZXNhbHQ"
             "$9qWtwbpyPd3vm1rB1GThgPzZ3/ydHL92zKL+15XZypg", Argon2_id);
    hashtest(version, 4, 16, 1, "password", "somesalt",
             "9025d48e68ef7395cca9079da4c4ec3affb3c8911fe4f86d1a2520856f63172c",
             "$argon2id$v=19$m=65536,t=4,p=1$c29tZXNhbHQ"
             "$kCXUjmjvc5XMqQedpMTsOv+zyJEf5PhtGiUghW9jFyw", Argon2_id);
    hashtest(version, 2, 16, 1, "differentpassword", "somesalt",
             "0b84d652cf6b0c4beaef0dfe278ba6a80df6696281d7e0d2891b817d8c458fde",
             "$argon2id$v=19$m=65536,t=2,p=1$c29tZXNhbHQ"
             "$C4TWUs9rDEvq7w3+J4umqA32aWKB1+DSiRuBfYxFj94", Argon2_id);
    hashtest(version, 2, 16, 1, "password", "diffsalt",
             "bdf32b05ccc42eb15d58fd19b1f856b113da1e9a5874fdcc544308565aa8141c",
             "$argon2id$v=19$m=65536,t=2,p=1$ZGlmZnNhbHQ"
             "$vfMrBczELrFdWP0ZsfhWsRPaHppYdP3MVEMIVlqoFBw", Argon2_id);

    /* Common error state tests */

    printf("\n");
    printf("Common error state tests\n");

    ret = argon2_hash(2, 1, 1, "password", strlen("password"),
                      "diffsalt", strlen("diffsalt"),
                      out, OUT_LEN, NULL, 0, Argon2_id, version);
    assert(ret == ARGON2_MEMORY_TOO_LITTLE);
    printf("Fail on invalid memory: PASS\n");

    ret = argon2_hash(2, 1 << 12, 1, NULL, strlen("password"),
                      "diffsalt", strlen("diffsalt"),
                      out, OUT_LEN, NULL, 0, Argon2_id, version);
    assert(ret == ARGON2_PWD_PTR_MISMATCH);
    printf("Fail on invalid null pointer: PASS\n");

    ret = argon2_hash(2, 1 << 12, 1, "password", strlen("password"), "s", 1,
                      out, OUT_LEN, NULL, 0, Argon2_id, version);
    assert(ret == ARGON2_SALT_TOO_SHORT);
    printf("Fail on salt too short: PASS\n");

    return 0;
}
