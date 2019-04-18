#ifndef _MEM_MANAGER_H
#define _MEM_MANAGER_H

#include <syscall.h>
#include <stdio.h>


void* my_malloc(int size);
void my_free(void* ptr);

#endif