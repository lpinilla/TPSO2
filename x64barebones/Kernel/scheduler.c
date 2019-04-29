#include <scheduler.h>
#include <list.h>
#include "process.c"

typedef struct schedulerADT{
    list_t p_ready;
    list_t p_waiting;
    list_t p_terminate;
} schedulerADT;

typedef schedulerADT * scheduler_t;

static scheduler_t scheduler;

void init_scheduler(){
    scheduler->p_ready= newList();
    scheduler->p_waiting = newList();
    scheduler->p_terminate = newList();
}

void add_process(scheduler_t scheduler, process_t process){
    pstate_t state = get_state(process);
    switch(state){
        case P_READY:
            addElement(scheduler->p_ready, process, sizeof(*process));
            break;
        case P_WAITING:
            addElement(scheduler->p_waiting, process, sizeof(*process));
            break;
        case P_TERMINATE:
            addElement(scheduler->p_terminate, process, sizeof(*process));
            break;
    }
}

void * switch_process(void * stack_pointer){
    process_t actual = getFirstElementReferece(scheduler->p_ready);
    set_stack_pointer(actual, stack_pointer);
    removeFirst(scheduler->p_ready);
    addElement(scheduler->p_ready, actual, sizeof(*actual));
    actual = getFirstElementReferece(scheduler->p_ready);
    return actual->stack_pointer;
}