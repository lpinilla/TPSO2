#ifndef _FREE_LIST_H
#define _FREE_LIST_H

#include <stddef.h>
#include <string.h>

enum STATUS {P = 0, F = 1};

struct t_Node{ 
    struct t_Node * next, *prev;
    void * mem_ptr;
    size_t size;
    enum STATUS status;
};

typedef struct t_Node * Node;

void * start_dir;

Node root, last;
size_t total_mem_size;

#endif

