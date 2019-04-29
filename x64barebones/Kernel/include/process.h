#ifndef _PROCESS_H
#define _PROCESS_H

#include <stdlib.h>

#define STACK_SIZE 4096

typedef enum {P_READY, P_RUNNING, P_WAITING, P_TERMINATE} pstate_t;

typedef struct processADT {
    size_t pid;
    pstate_t state;
    char * stack_pointer;
} processADT;

typedef struct processADT * process_t;

process_t create_process(void * process_start);
void delete_process(process_t process);
void set_state(process_t process, pstate_t state);
pstate_t get_state(process_t process);
void set_stack_pointer(process_t process, void * stack_pointer);

#endif