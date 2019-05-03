#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include <list.h>
#include <process.h>
#include <interrupts.h>
#include <graphics.h>

void init_scheduler();
void run_process(process_t process);
uint64_t switch_process(uint64_t stack_pointer);
char ** get_current_processes();

#endif

