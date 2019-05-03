#ifndef _PROCESS_H
#define _PROCESS_H

#include <stdlib.h>
#include <mem_manager.h>
#include <stdint.h>
#include <lib.h>
#include <graphics.h>

#define STACK_SIZE 4096

#define MAX_PROCESS_NAME 257

typedef enum {P_READY, P_RUNNING, P_WAITING, P_TERMINATE} pstate_t;

typedef struct processADT {
	char * name[MAX_PROCESS_NAME];
    size_t pid;
    pstate_t state;
	uint64_t stack_start;
    uint64_t stack_pointer;
} processADT;

typedef struct processADT * process_t;

process_t create_process(uint64_t process_start, char * name);
void delete_process(process_t process);
void set_state(process_t process, pstate_t state);
pstate_t get_state(process_t process);
void set_stack_pointer(process_t process, uint64_t stack_pointer);
void kill_process();
void print_process(process_t process);

#endif