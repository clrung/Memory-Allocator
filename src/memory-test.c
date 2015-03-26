#include <stdio.h>
#include <stdlib.h>

#include "allocator.h"

int main(int argc, char* argv[]) {
	#ifdef FIRST_FIT
		printf("\nFIRST FIT ALLOCATION:\n\n");
		printf("Initializing the lists...\n");
		if(allocator_init(12) == -1) {
		    perror("ERROR: malloc failed.\n");
		}
	
		printf("Requesting 3 bytes of data...\n");
		if(allocate(3) == start_memory)
			printf("allocate(3) success!\n");
		else
			printf("allocate(3) failed.\n");
		
		printf("Requesting 4 bytes of data...\n");
		if(allocate(4) == start_memory + 3)
			printf("allocate(4) success!\n");
		else
			printf("allocate(4) failed.\n");

		printf("Requesting 1 bytes of data...\n");
		if(allocate(1) == start_memory + 7)
			printf("allocate(1) success!\n");
		else
			printf("allocate(1) failed.\n");

		printf("Deallocating 4 bytes of memory at position %lu...\n", (long unsigned int)start_memory + 3);
		if(deallocate(start_memory + 3) == 0)
			printf("deallocate(%lu) success!\n", (long unsigned int)start_memory + 4);
		else
			printf("deallocate(%lu) failed.\n", (long unsigned int)start_memory + 4);
	
		printf("Requesting 3 bytes of data...\n");
		if(allocate(3) == start_memory + 8)
			printf("allocate(3) success!\n");
		else
			printf("allocate(3) failed.\n");
		
		printf("Requesting 2 bytes of data...\n");
		if(allocate(2) == start_memory + 3)
			printf("allocate(2) success!\n");
		else
			printf("allocate(2) failed.\n");
		
		printf("\nAt this point, we have 2 bytes free from 5-7 and one byte free from 11-12.\n\n");
	
		printf("Requesting 4 bytes of data...\n");
		if(allocate(3) == start_memory + 8)
			printf("allocate(4) success!\n");
		else
			printf("allocate(4) failed, as it should.\n");
		
		printf("Deallocating 3 bytes of memory at position %lu...\n", (long unsigned int)start_memory + 8);
		if(deallocate(start_memory + 8) == 0)
			printf("deallocate(%lu) success!\n", (long unsigned int)start_memory + 4);
		else
			printf("deallocate(%lu) failed.\n", (long unsigned int)start_memory + 4);
		
		printf("Requesting 4 bytes of data, since we should now have space...\n");
		if(allocate(3) == start_memory + 8)
			printf("allocate(4) success!\n");
		else
			printf("allocate(4) failed.\n");
	#elif BEST_FIT
		printf("\nBEST FIT ALLOCATION:\n\n");
		printf("Initializing the lists...\n");
		if(allocator_init(12) == -1) {
		    perror("ERROR: malloc failed.\n");
		}
	
		printf("Requesting 5 bytes of data...\n");
		if(allocate(5) == start_memory)
			printf("allocate(5) success!\n");
		else
			printf("allocate(5) failed.\n");
		
		printf("Requesting 3 bytes of data...\n");
		if(allocate(3) == start_memory + 5)
			printf("allocate(3) success!\n");
		else
			printf("allocate(3) failed.\n");

		printf("Requesting 2 bytes of data...\n");
		if(allocate(2) == start_memory + 8)
			printf("allocate(2) success!\n");
		else
			printf("allocate(2) failed.\n");
			
		printf("Requesting 2 bytes of data...\n");
		if(allocate(2) == start_memory + 10)
			printf("allocate(2) success!\n");
		else
			printf("allocate(2) failed.\n");

		printf("Deallocating 2 bytes of memory at position %lu...\n", (long unsigned int)start_memory + 8);
		if(deallocate(start_memory + 8) == 0)
			printf("deallocate(%lu) success!\n", (long unsigned int)start_memory + 8);
		else
			printf("deallocate(%lu) failed.\n", (long unsigned int)start_memory + 8);
			
		printf("Deallocating 5 bytes of memory at position %lu...\n", (long unsigned int)start_memory);
		if(deallocate(start_memory) == 0)
			printf("deallocate(%lu) success!\n", (long unsigned int)start_memory);
		else
			printf("deallocate(%lu) failed.\n", (long unsigned int)start_memory);
			
		printf("Requesting 2 bytes of data...\n");
		if(allocate(2) == start_memory + 8)
			printf("allocate(2) success! This even put the 2 bytes of memory in the correct position for best fit.\n");
		else
			printf("allocate(2) failed.\n");
			
	#elif WORST_FIT
		printf("\nWORST FIT ALLOCATION:\n\n");
		printf("Initializing the lists...\n");
		if(allocator_init(12) == -1) {
		    perror("ERROR: malloc failed.\n");
		}
	
		printf("Requesting 3 bytes of data...\n");
		if(allocate(3) == start_memory)
			printf("allocate(3) success!\n");
		else
			printf("allocate(3) failed.\n");
		
		printf("Requesting 5 bytes of data...\n");
		if(allocate(5) == start_memory + 3)
			printf("allocate(5) success!\n");
		else
			printf("allocate(5) failed.\n");

		printf("Requesting 2 bytes of data...\n");
		if(allocate(2) == start_memory + 8)
			printf("allocate(2) success!\n");
		else
			printf("allocate(2) failed.\n");
			
		printf("Requesting 2 bytes of data...\n");
		if(allocate(2) == start_memory + 10)
			printf("allocate(2) success!\n");
		else
			printf("allocate(2) failed.\n");

		printf("Deallocating 2 bytes of memory at position %lu...\n", (long unsigned int)start_memory + 8);
		if(deallocate(start_memory + 8) == 0)
			printf("deallocate(%lu) success!\n", (long unsigned int)start_memory + 8);
		else
			printf("deallocate(%lu) failed.\n", (long unsigned int)start_memory + 8);
			
		printf("Deallocating 5 bytes of memory at position %lu...\n", (long unsigned int)start_memory + 3);
		if(deallocate(start_memory + 3) == 0)
			printf("deallocate(%lu) success!\n", (long unsigned int)start_memory + 3);
		else
			printf("deallocate(%lu) failed.\n", (long unsigned int)start_memory + 3);
			
		printf("Requesting 2 bytes of data...\n");
		if(allocate(2) == start_memory + 3)
			printf("allocate(2) success! This even put the 2 bytes of memory in the correct position for worst fit.\n");
		else
			printf("allocate(2) failed.\n");
	#endif
}
