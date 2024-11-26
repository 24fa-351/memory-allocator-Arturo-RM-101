#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "malloc.h"

#define TEST_SIZE 10
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int rand_between(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main(int argc, char *argv[]) {
    srand(1000);

    char* testing_string = "This will be the string that wil be tested";

    char *ptrs[TEST_SIZE];

    printf("---------Allocating memory---------\n");

    for (int ix = 0; ix < TEST_SIZE; ix++) {
        int size = rand_between(1, 100);

        ptrs[ix] = (char *) malloc(size);

        if (ptrs[ix] == NULL) {
            printf("[%d] Failed to allocate memory\n", ix);
            return 1;
        }

        fprintf(stderr, "[%d] Allocating %d bytes\n", ix, size);

        int length_to_copy = MIN(strlen(testing_string), size);

        strncpy(ptrs[ix], testing_string, length_to_copy);
        ptrs[ix][length_to_copy] = '\0';

    }

    printf("--------Reallocating memory--------\n");

    for (int ix = 0; ix < TEST_SIZE; ix++) {
        int size = rand_between(1, 50);
        fprintf(stderr, "[%d] New size: %d\n", ix, size);

        ptrs[ix] = (char *) realloc(ptrs[ix], size);

        if (ptrs[ix] == NULL) {
            printf("[%d] Failed to reallocate memory\n", ix);
            return 1;
        }

        int length_to_copy = MIN(strlen(testing_string), size);

        fprintf(stderr, "[%d] ptrs[%d]: %p, going to copy %d chars\n", ix, ix, ptrs[ix], length_to_copy);

        strncpy(ptrs[ix], testing_string, length_to_copy);

        ptrs[ix][length_to_copy] = '\0';

        fprintf(stderr, "[%x] %s\n\n", ix, ptrs[ix]);
    }

}