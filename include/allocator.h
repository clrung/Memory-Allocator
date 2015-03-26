#include <stddef.h>

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

struct block {
	void* start;
	size_t size;
};

struct dlist* free_list;
struct dlist* allocated_list;
void* start_memory;

int allocator_init(size_t size);

void *allocate(size_t size);

int deallocate(void *ptr);

#endif
