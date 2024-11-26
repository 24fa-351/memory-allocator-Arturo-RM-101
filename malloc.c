#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"

#define TEST_SIZE 10
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int rand_between(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main(int argc, char *argv[]) {
    srand(2020);

    char* testing_string = "This will be the string that wil be tested";

    char *ptrs[TEST_SIZE];

    for (int i = 0; i < TEST_SIZE; i++) {
        int size = rand_between(1, 100);
        ptrs[i] = (char *) malloc(size);
        if (ptrs[i] == NULL) {
            printf("Failed to allocate memory\n");
            return 1;
        }
        printf("Allocated %d bytes at %p\n", size, ptrs[i]);
    }
}