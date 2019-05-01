#ifndef _PROCESS_H
#define _PROCESS_H

#include <stdlib.h>
#include <mem_manager.h>
#include <stdint.h>

#define STACK_SIZE 4096

typedef enum {P_READY, P_RUNNING, P_WAITING, P_TERMINATE} pstate_t;

typedef struct processADT {
    size_t pid;
    pstate_t state;
    uint64_t stack_pointer;
} processADT;

typedef struct processADT * process_t;

typedef struct {
	//Registers restore context
	uint64_t gs;
	uint64_t fs;
	uint64_t r15;
	uint64_t r14;
	uint64_t r13;
	uint64_t r12;
	uint64_t r11;
	uint64_t r10;
	uint64_t r9;
	uint64_t r8;
	uint64_t rsi;
	uint64_t rdi;
	uint64_t rbp;
	uint64_t rdx;
	uint64_t rcx;
	uint64_t rbx;
	uint64_t rax;

	//iretq hook
	uint64_t rip;
	uint64_t cs;
	uint64_t eflags;
	uint64_t rsp;
	uint64_t ss;
	uint64_t base;
}stack_t;

process_t create_process(uint64_t process_start);
void delete_process(process_t process);
void set_state(process_t process, pstate_t state);
pstate_t get_state(process_t process);
void set_stack_pointer(process_t process, uint64_t stack_pointer);

#endif