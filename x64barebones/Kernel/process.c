#include <stdlib.h>

#define STACK_SIZE 4096

typedef enum {P_START, P_READY, P_RUNNING, P_WAITING, P_TERMINATE} pstate_t;

static size_t global_pid;

typedef struct {
    size_t pid;
    pstate_t state;
    char * stack;
} process_t;

process_t * create_process(){
    process_t * new_process = mem_alloc(sizeof(process_t));
    new_process->pid = global_pid;
    global_pid++;
    new_process->state = P_START;
    new_process->stack = mem_alloc(sizeof(STACK_SIZE));
    return new_process;
}

void delete_process(process_t * process){
    free_mem(process->stack);
    free_mem(process);
}