#include "allocator.h"
#include "dlist.h"
#include "dnode.h"

#include <stdio.h>
#include <stdlib.h>

struct block* block;
void *data;

int allocator_init(size_t size) {
	free_list = dlist_create();
	allocated_list = dlist_create();

	start_memory = malloc(size);

	if(start_memory == NULL) {
		return -1;
	} else {
		struct block* block = malloc(sizeof(struct block));
		block->start = start_memory;
		block->size = size;
		dlist_add_front(free_list, block);
	}

	return 0;
}

// Allocates memory in first space that is large enough
// to hold the size.
void *allocateFF(size_t size) {
	block = dlist_iter_begin(free_list);

	// if the list is empty, don't enter
	if(block != NULL) {
		for(int i = 0; i < free_list->counter; i++) {
			data = block->start;
			if(size == block->size) {
				dlist_find_remove(free_list, block);
				dlist_add_back(allocated_list, block);
				return data;
			} else if(size < block->size) {
				struct block* new_block = malloc(sizeof(struct block));
				new_block->size = size;
				new_block->start = block->start;
				block->size = block->size - size;
				block->start = block->start + size;
				dlist_add_back(allocated_list, new_block);
				return data;
			}
			block = dlist_iter_next(free_list);
		}
	}
	return NULL;
}

// Allocates memory in the smallest space that is large
// enough to hold the size.
void *allocateBF(size_t size) {
	block = dlist_iter_begin(free_list);
	struct block* smallest = NULL;

	// if the list is empty, don't enter
	if(block != NULL) {
		for(int i = 0; i < free_list->counter; i++) {
			if(block->size >= size) {
				if(smallest == NULL || block->size < smallest->size)
					smallest = block;
					smallest->size = block->size;
			}
			block = dlist_iter_next(free_list);
		}
		data = smallest->start;
		if(size == smallest->size) {
			dlist_find_remove(free_list, smallest);
			dlist_add_back(allocated_list, smallest);
			return data;
		} else if(size < smallest->size) {
			struct block* new = malloc(sizeof(struct block));
			new->start = smallest->start;
			new->size = smallest->size;
			smallest->size -= size;
			smallest->start += size;
			dlist_add_back(allocated_list, new);
			return data;
		}
	}
	return NULL;
}

// Allocates memory in the largest space available.
void *allocateWF(size_t size) {
	block = dlist_iter_begin(free_list);
	struct block* largest = NULL;

	// if the list is empty, don't enter
	if(block != NULL) {
		for(int i = 0; i < free_list->counter; i++) {
			if(block->size >= size) {
				if(largest == NULL || block->size > largest->size)
					largest = block;
					largest->size = block->size;
			}
			block = dlist_iter_next(free_list);
		}
		data = largest->start;
		if(size == largest->size) {
			dlist_find_remove(free_list, largest);
			dlist_add_back(allocated_list, largest);
			return data;
		} else if(size < largest->size) {
			struct block* new = malloc(sizeof(struct block));
			new->start = largest->start;
			new->size = largest->size;
			largest->size -= size;
			largest->start += size;
			dlist_add_back(allocated_list, new);
			return data;
		}
	}

	return NULL;
}

void *allocate(size_t size) {
	#ifdef FIRST_FIT
		return allocateFF(size);
	#elif BEST_FIT
		return allocateBF(size);
	#elif WORST_FIT
		return allocateWF(size);
	#endif
}

int deallocate(void *ptr) {
	block = dlist_iter_begin(allocated_list);
	if(block != NULL) {
		for(int i = 0; i < allocated_list->counter; i++) {
			if(ptr == block->start) {
				dlist_find_remove(allocated_list, block);
				dlist_add_back(free_list, block);
				return 0;
			}
			block = dlist_iter_next(allocated_list);
		}
	}
	return -1;
}