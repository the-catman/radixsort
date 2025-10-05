#ifndef RADIX_H
#define RADIX_H

#include <stdint.h>
#include <stddef.h>

/**
 * Sort an array of 32-bit unsigned integers in-place
 * @returns Status code: 0 = success, 1 = fail
 */
int radixSort(uint32_t **arrPtr, const size_t len);

#endif
