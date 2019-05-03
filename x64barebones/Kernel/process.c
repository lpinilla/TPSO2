#include <process.h>
#include <graphics.h>

static uint64_t init_stack(void * process_start, void * stack_pointer); 

static size_t global_pid = 0;

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

process_t create_process(char * name, void * process_start){
    process_t new_process = mem_alloc(sizeof(*new_process));
	new_process->name = name;
    new_process->pid = global_pid++;
    new_process->state = P_READY;
	new_process->stack_pointer = mem_alloc(STACK_SIZE);
    new_process->stack_pointer = init_stack(process_start, new_process->stack_pointer);

    return new_process;
}

void delete_process(process_t process){
    free_mem((void *)process->stack_pointer);
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

static uint64_t init_stack(void * process_start, void * stack_pointer) {
    stack_t * frame = (stack_t *)(stack_pointer + STACK_SIZE - sizeof(stack_t) -1 );

	frame->gs = 0x001;
	frame->fs =	0x002;
	frame->r15 = 0x003;
	frame->r14 = 0x004;
	frame->r13 = 0x005;
	frame->r12 = 0x006;
	frame->r11 = 0x007;
	frame->r10 = 0x008;
	frame->r9 =	0x009;
	frame->r8 =	0x00A;
	frame->rsi = 0x00B;
	frame->rdi = 0x00C;
	frame->rbp = 0x00D;
	frame->rdx = 0x00E;
	frame->rcx = 0x00F;
	frame->rbx = 0x010;
	frame->rax = 0x011;

	frame->rip = (uint64_t)process_start;
	frame->cs =	0x008;
	frame->eflags = 0x202;
	frame->rsp = (uint64_t)&(frame->base);
	frame->ss = 0x000;
	frame->base = 0x000;

	return (void *)frame;
}