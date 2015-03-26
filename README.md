# Memory Allocator
I wrote this memory allocator for my Operating Systems class while at Bucknell.  You may choose to allocate memory using three policies:
* First-Fit
  * Allocates space in the first hole it encounters that is large enough to satisfy the request
  * Best time efficiency
  * Poor space efficiency
* Worst-Fit
  * Allocates space in the largest block of unallocated memory available
  * Worst space efficiency
  * Worst time efficiency due to a full pass requirement.
* Best-Fit
  * Allocates space in the smallest block of unallocated memory in which it will fit
  * Best space efficiency
  * Worst time efficiency due to a full pass requirement.

To choose which policy to use, edit the Makefile’s define flag.  The default is the worst fit allocation policy.
There is an included test file, memory-test.c, that will test allocating and deallocating various sizes of memory.

## Usage
```
$ make
$ ./bin/memory-test
```