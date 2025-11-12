#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "radix.h"
#include "random.h"
#include "util.h"

int main(void) {
    size_t len = 100000000;
    uint32_t *arr = malloc(len * sizeof(uint32_t));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    uint32_t state = (uint32_t)time(NULL);

    for (size_t i = 0; i < len; i++)
        arr[i] = rand32(&state);

    printf("Created array, sorting...\n");

    clock_t now = clock();
    int status = radixSort(&arr, len);
    clock_t end = clock();

    if(status == 0) {
        double time_taken = ((double)(end - now)) / CLOCKS_PER_SEC;
        printf("Time taken: %f seconds\n", time_taken);

        if (isSorted(arr, len))
            printf("Test passed: Array is sorted.\n");
        else
            fprintf(stderr, "Error: Array is not sorted!\n");        
    } else {
        fprintf(stderr, "Error: Allocation failed.\n");
    }

    free(arr);
    return 0;
}
