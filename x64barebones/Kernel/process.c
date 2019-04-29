#include <stdlib.h>

#define STACK_SIZE 4096

typedef enum {P_READY, P_RUNNING, P_WAITING, P_TERMINATE} pstate_t;
typedef processADT * process_t;

static size_t global_pid;

typedef struct {
    size_t pid;
    pstate_t state;
    char * stack_pointer;
} processADT;

process_t create_process(void * process_start){
    process_t new_process = mem_alloc(sizeof(processADT));
    new_process->pid = global_pid;
    global_pid++;
    new_process->state = P_READY;
    new_process->stack = mem_alloc(sizeof(STACK_SIZE));
    return new_process;
}

void delete_process(process_t process){
    free_mem(process->stack);
    free_mem(process);
}

void set_state(process_t process, pstate_t state){
    process->state = state;
}
pstate_t get_state(process_t process){
    return process->state;
}