#ifndef RANDOM_H
#define RANDOM_H

#include <stdint.h>

// Xorshift32 PRNG
uint32_t rand32(uint32_t *state);

#endif
