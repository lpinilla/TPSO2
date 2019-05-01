#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include <list.h>
#include <process.h>
#include <interrupts.h>

typedef struct schedulerADT{
    list_t p_ready;
    list_t p_waiting;
    list_t p_terminate;
} schedulerADT;

typedef struct schedulerADT * scheduler_t;

void init_scheduler();
void run_process(process_t process);
void add_process(process_t process);
uint64_t switch_process(uint64_t stack_pointer);

#endif

