#include "util.h"

bool isSorted(const uint32_t *arr, size_t len) {
    for (size_t i = 1; i < len; ++i)
        if (arr[i - 1] > arr[i]) return false;
    return true;
}
