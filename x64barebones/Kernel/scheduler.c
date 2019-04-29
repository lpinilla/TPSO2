#include <scheduler.h>
#include <list.h>
#include "process.c"

typedef schedulerADT * scheduler_t;

typedef struct {
    list_t p_ready;
    list_t p_waiting;
    list_t p_terminate;
} schedulerADT;

void init_scheduler(scheduler_t scheduler){
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