#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <syscall.h>


void* my_malloc(int size);
void free(void* ptr);

#endif