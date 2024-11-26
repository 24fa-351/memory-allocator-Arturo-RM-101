#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>

void* malloc_memory(size_t size);
void free_memory(void* ptr);
void* realloc_memory(void* ptr, size_t size);

void* get_me_blocks(__ssize_t how_much);

#endif