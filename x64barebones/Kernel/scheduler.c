#include <scheduler.h>


typedef struct nodeADT *node_t;

typedef struct nodeADT{
    process_t element;
    node_t prev;
    node_t next;
}nodeADT;

static void set_next_process();

//LISTA DE NODOS CIRCULAR PARA LOS PROCESOS
static node_t current_process;
static size_t number_of_processes;

void init_scheduler(){
    current_process = NULL;
    number_of_processes = 0;
}

void run_process(process_t process){
    number_of_processes++;
    if(current_process == NULL){
        current_process = mem_alloc(sizeof(nodeADT));
        current_process->element = process;
        current_process->next = current_process;
        current_process->prev = current_process;
        _change_process(process->stack_pointer);
    }
    else{
        node_t aux = mem_alloc(sizeof(nodeADT));
        aux->element = process;
        aux->next = current_process->next;
        aux->prev = current_process;
        current_process->next->prev = aux;
        current_process->next = aux;
    }
}

void kill_process(){

    number_of_processes--;

    node_t aux = current_process;
    current_process->prev->next = current_process->next;
    current_process->next->prev = current_process->prev;

    set_next_process();

    delete_process(aux->element);
    free_mem(aux);

    _change_process(current_process->element->stack_pointer);
}

static void set_next_process(){
    current_process = current_process->next;
    if(current_process->element->state == P_TERMINATE){
        kill_process();
    }
    else if(current_process->element->state == P_WAITING){
        set_next_process();
    }
    else if(current_process->element->state == P_READY){
        current_process->element->state = P_RUNNING;
    }
}

//Esto se llama desde el iqr handler que seria mas rapido que el timer creo, asi nos acercamos
// lo mas posible a un quantum como pide la consigna
uint64_t switch_process(uint64_t stack_pointer){
    if(number_of_processes>1){
        current_process->element->stack_pointer = stack_pointer;

        set_next_process();

        return current_process->element->stack_pointer;
    }
    else {
        return stack_pointer;
    }
}

char ** get_current_processes(){
    char **result = mem_alloc(number_of_processes*sizeof(void *));
    //Vector de strings con el formato "PID: pid PROCESS: process_name \n"
    //Falta hacer

    return result;
}