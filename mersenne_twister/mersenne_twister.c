/**
 * An MT19937-64 implementation
 */

#include <assert.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <sys/time.h>

#define w 64
#define n 312
#define m 156
#define r 31
#define a 0xB5026F5AA96619E9
#define u 29
#define d 0x5555555555555555
#define s 17
#define b 0x71D67FFFEDA60000
#define t 37
#define c 0xFFF7EEE000000000
#define l 43
#define f 6364136223846793005

const int64_t 
    lower_mask = (1U << r) - 1,
    upper_mask = (~lower_mask);

int64_t stateArr[n];

int_fast16_t ind = n + 1;

void seed_mersenne_twister(int64_t seed) {
    ind = n;
    stateArr[0] = seed;
    for (int_fast16_t i = 1; i < n; i++) {
        stateArr[i] = (f * (stateArr[i - 1] ^ (stateArr[i - 1] >> (w - 2))) + i);
    }
}

void twister(void) {
    for (int_fast16_t i = 0; i < n; i++) {
        int64_t x = (stateArr[i] & upper_mask) + (stateArr[(i + 1) % n] & lower_mask);
        int64_t xA = x >> 1;
        if (x % 2 != 0) {
            xA = xA ^ a;
        }
        stateArr[i] = stateArr[(i + m) % n] ^ xA;
    }
    ind = 0;
}

int64_t get_number(void) {
    assert(ind <= n);
    if (ind == n) {
        twister();
    }
    int64_t y = stateArr[ind];
    y = y ^ ((y >> u) & d);
    y = y ^ ((y << s) & b);
    y = y ^ ((y << t) & c);
    y = y ^ (y >> l);
    ind++;
    return y;
}

void main(void) {
    int_fast64_t how_many = 0;
    printf("Using system microseconds as the seed...\n");
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    seed_mersenne_twister(current_time.tv_usec);

    printf("Please enter how many random numbers you wish to generate: ");
    scanf("%" SCNdFAST64, &how_many);
    // printf("\n");
    for (int_fast64_t i = 1; i <= how_many; i++) {
        printf("Random number #%" PRIdFAST64 " is: %" PRId64 "\n", i, get_number());
    }
}






