#include <process.h>
#include <graphics.h>

static uint64_t init_stack(uint64_t process_start, uint64_t stack_pointer); 

static size_t global_pid = 0;

process_t create_process(uint64_t process_start){

    process_t new_process = (process_t)mem_alloc(sizeof(*new_process));
    new_process->pid = global_pid++;
    new_process->state = P_READY;
	new_process->stack_pointer = (uint64_t)mem_alloc(STACK_SIZE);
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

static uint64_t init_stack(uint64_t process_start, uint64_t stack_pointer) {
    stack_t * frame = (stack_t *)stack_pointer;

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

	frame->rip = process_start;
	frame->cs =	0x008;
	frame->eflags = 0x202;
	frame->rsp = (uint64_t)&(frame->base);
	frame->ss = 0x000;
	frame->base = 0x000;

	return (uint64_t)frame;
}