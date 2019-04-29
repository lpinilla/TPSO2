#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include <list.h>
#include <process.h>

typedef struct schedulerADT * scheduler_t;

void init_scheduler();
void add_process(scheduler_t scheduler, process_t process);
void * switch_process(void * stack_pointer)

#endif

