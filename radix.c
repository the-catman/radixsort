#include "radix.h"
#include <stdlib.h>

#define BITS 11                  // Radix bits
#define BASE (1u << (BITS))      // Bucket count/base
#define MASK (BASE - 1u)         // Mask for digit extraction

int radixSort(uint32_t **arrPtr, const size_t len) {
    if (len <= 1) return 0;

    uint32_t *arr = *arrPtr;
    uint32_t *output = malloc(len * sizeof(uint32_t));
    uint32_t *count = malloc(BASE * sizeof(uint32_t));

    if (!output || !count) {
        return 1; // Allocation failed
    }

    uint32_t max = arr[0];
    for (size_t i = 1; i < len; ++i)
        if (arr[i] > max) max = arr[i];

    uint32_t max_bits = (max == 0) ? 1 : (32 - __builtin_clz(max));

    for (uint32_t shift = 0; shift < max_bits; shift += BITS) {
        // Reset counts
        for (uint32_t j = 0; j < BASE; ++j)
            count[j] = 0;

        // Count digit occurrences
        for (size_t j = 0; j < len; ++j)
            count[(arr[j] >> shift) & MASK]++;

        // Accumulate counts
        for (uint32_t j = 1; j < BASE; ++j)
            count[j] += count[j - 1];

        // Place elements into output array
        for (int64_t j = (int64_t)len - 1; j >= 0; --j)
            output[--count[(arr[j] >> shift) & MASK]] = arr[j];

        // Swap input/output buffers
        uint32_t *tmp = arr;
        arr = output;
        output = tmp;
    }

    free(output);
    free(count);
    *arrPtr = arr;

    return 0;
}
