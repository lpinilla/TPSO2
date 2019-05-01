#include <scheduler.h>
#include <graphics.h>

static scheduler_t scheduler;

void init_scheduler(){
    scheduler = mem_alloc(sizeof(schedulerADT));
    scheduler->p_ready= newList();
    scheduler->p_waiting = newList();
    scheduler->p_terminate = newList();
}

void run_process(process_t process){
    //Esta funcion es para correr el primer proceso nomas, porque si usamos directamente _context_switch estaria mal
    _change_process(process->stack_pointer);
}

void add_process(process_t process){
    pstate_t state = get_state(process);
    switch(state){
        case P_READY:
            addElement(scheduler->p_ready, process, sizeof(processADT));
            break;
        case P_WAITING:
            addElement(scheduler->p_waiting, process, sizeof(*process));
            break;
        case P_TERMINATE:
            addElement(scheduler->p_terminate, process, sizeof(*process));
            break;
        case P_RUNNING:
            break; //ver!
    }
}

uint64_t switch_process(uint64_t stack_pointer){
    process_t actual = getFirstElementReferece(scheduler->p_ready);
    set_stack_pointer(actual, stack_pointer);
    removeFirst(scheduler->p_ready);
    addElement(scheduler->p_ready, actual, sizeof(*actual));
    actual = getFirstElementReferece(scheduler->p_ready);
    return actual->stack_pointer;
}