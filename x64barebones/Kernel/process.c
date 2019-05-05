#include <process.h>

typedef struct processADT {
	char * name[MAX_PROCESS_NAME];
    size_t pid;
    pstate_t state;
	uint64_t stack_start;
    uint64_t stack_pointer;
} processADT;

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

static uint64_t init_stack(process_t process, uint64_t process_start, uint64_t stack_pointer); 
static void process_caller(process_t process, uint64_t process_start);

static size_t global_pid = 0;
static process_t all_processes[MAX_PROCESSES];

process_t create_process(uint64_t process_start, char * process_name){

    process_t new_process = (process_t)mem_alloc(sizeof(*new_process));
	str_cpy(process_name, (char*)(new_process->name));
    new_process->pid = global_pid;
    new_process->state = P_READY;
	new_process->stack_start = (uint64_t)mem_alloc(STACK_SIZE);
    new_process->stack_pointer = init_stack(new_process, process_start, new_process->stack_start);
	all_processes[global_pid++] = new_process;

    return new_process;
}

void delete_process(process_t process){
    free_mem((void *)process->stack_start);
    free_mem(process);
}

void set_state(process_t process, pstate_t state){
    process->state = state;
}

pstate_t get_state(process_t process){
    return process->state;
}

void set_stack_pointer(process_t process, uint64_t stack_pointer){
    process->stack_pointer=stack_pointer;
}

void set_state_id(size_t pid, pstate_t state){
	all_processes[pid]->state = state;
}

size_t get_pid(process_t process){
	return process->pid;
}

uint64_t get_stack_pointer(process_t process){
	return process->stack_pointer;
}

static uint64_t init_stack(process_t process, uint64_t process_start, uint64_t stack_pointer) {
    stack_t * frame = (stack_t *)(stack_pointer + STACK_SIZE - sizeof(stack_t) - 1);

	frame->gs = 0x000;
	frame->fs =	0x000;
	frame->r15 = 0x000;
	frame->r14 = 0x000;
	frame->r13 = 0x000;
	frame->r12 = 0x000;
	frame->r11 = 0x000;
	frame->r10 = 0x000;
	frame->r9 =	0x000;
	frame->r8 =	0x000;
	frame->rsi = process_start;
	frame->rdi = (uint64_t)process;
	frame->rbp = 0x000;
	frame->rdx = 0x000;
	frame->rcx = 0x000;
	frame->rbx = 0x000;
	frame->rax = 0x000;

	frame->rip = (uint64_t)process_caller;
	frame->cs =	0x008;
	frame->eflags = 0x202;
	frame->rsp = (uint64_t)&(frame->base);
	frame->ss = 0x000;
	frame->base = 0x000;

	return (uint64_t)frame;
}

void print_process(process_t process){
	draw_string("PID: ");
	draw_number(process->pid);
	draw_string(" PROCESS NAME: ");
	draw_string((char *)process->name);
	draw_string(" STATE: ");
	if(process->state == P_READY){
		draw_string("P_READY");
	}
	else if(process->state == P_RUNNING){
		draw_string("P_RUNNING");
	}
	else if(process->state == P_WAITING){
		draw_string("P_WAITING");
	}
	else{
		draw_string("P_TERMINATE");
	}
	new_line();
}

static void process_caller(process_t process, uint64_t process_start){
	void (*process_call)(void) = (void (*)(void))process_start;
	(*process_call)();
	kill_process();
}

pstate_t get_state_id(size_t pid){
	return all_processes[pid]->state;
}