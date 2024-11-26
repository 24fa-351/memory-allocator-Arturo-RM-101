#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"

typedef struct block {
    size_t size;
    struct block* next;
} block_t;

static block_t* free_list = NULL;
#define ALIGNMENT_SIZE 8

size_t align_size(size_t size) {
    return (size + ALIGNMENT_SIZE - 1) & ~(ALIGNMENT_SIZE - 1);
}

void* get_me_blocks(ssize_t how_much) {
    void* ptr = sbrk(0);
    if (sbrk(how_much) == (void*)-1) {
        return NULL;
    }
    return ptr;
}

void* malloc_memory(size_t size) {
    size = align_size(size);

    block_t* prev = NULL;
    block_t* current = free_list;

    while (current != NULL) {
        if (current->size >= size) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                free_list = current->next;
            }
            return (void*)((char*)current + sizeof(block_t));
        }
        prev = current;
        current = current->next;
    }

    block_t* block = (block_t*)get_me_blocks(sizeof(block_t) + size);

    if (block == NULL) {
        return NULL;
    }

    block -> size = size;
    block -> next = NULL;
    return (void*)((char*)block + sizeof(block_t));
}

void free_memory(void* ptr) {
    if (ptr == NULL) {
        return;
    }
    
    block_t* block = (block_t*)((char*)ptr - sizeof(block_t));
    block -> next = free_list;
    free_list = block;
}

void* realloc_memory(void* ptr, size_t realloc_size) {
    if (ptr == NULL) {
        return malloc_memory(realloc_size);
    }
    if (realloc_size == 0) {
        free_memory(ptr);
        return NULL;
    }
    
    block_t* block = (block_t*)((char*)ptr - sizeof(block_t));
    size_t previous_size = block -> size;

    if (realloc_size <= previous_size) {
        return ptr;
    }

    void* new_ptr = malloc_memory(realloc_size);
    if (new_ptr == NULL) {
        return NULL;
    }

    memcpy(new_ptr, ptr, previous_size);
    free_memory(ptr);

    return new_ptr;
}