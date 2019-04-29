#include <process.h>
#include <graphics.h>

static size_t global_pid;
static void * init_stack(void * process_start, void * stack_pointer); 

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


process_t create_process(void * process_start){
    process_t new_process = mem_alloc(sizeof(processADT));
    new_process->pid = global_pid;
    global_pid++;
    new_process->state = P_READY;
    new_process->stack_pointer = mem_alloc(sizeof(STACK_SIZE));
    new_process->stack_pointer = init_stack(new_process, new_process->stack_pointer);
    return new_process;
}

void delete_process(process_t process){
    free_mem(process->stack_pointer);
    free_mem(process);
}

void set_state(process_t process, pstate_t state){
    process->state = state;
}
pstate_t get_state(process_t process){
    return process->state;
}

void set_stack_pointer(process_t process, void * stack_pointer){
    process->stack_pointer=stack_pointer;
}

static void * init_stack(void * process_start, void * stack_pointer) {
    stack_t * frame = (stack_t *) (stack_pointer + STACK_SIZE - sizeof( *frame) - 1);
	draw_string("Llegue1");
	frame->gs = 0x000;
	draw_string("Llegue2");
	frame->fs =	0x000;
	frame->r15 = 0x000;
	frame->r14 = 0x000;
	frame->r13 = 0x000;
	frame->r12 = 0x000;
	frame->r11 = 0x000;
	frame->r10 = 0x000;
	frame->r9 =	0x000;
	frame->r8 =	0x000;
	frame->rsi = 0x000;
	frame->rdi = 0x000;
	frame->rbp = 0x000;
	frame->rdx = 0x000;
	frame->rcx = 0x000;
	frame->rbx = 0x000;
	frame->rax = 0x000;
	frame->rip =	(uint64_t)&process_start;
	frame->cs =		0x008;
	frame->eflags = 0x202;
	frame->rsp =	(uint64_t)&(frame->base);
	frame->ss = 	0x000;
	frame->base =	0x000;

	return frame;
}