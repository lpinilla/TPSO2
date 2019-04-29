#include <process.h>

static size_t global_pid;

process_t create_process(void * process_start){
    process_t new_process = mem_alloc(sizeof(processADT));
    new_process->pid = global_pid;
    global_pid++;
    new_process->state = P_READY;
    new_process->stack_pointer = mem_alloc(sizeof(STACK_SIZE));
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