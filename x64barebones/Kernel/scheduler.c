#include <scheduler.h>


typedef struct nodeADT *node_t;

typedef struct nodeADT{
    process_t element;
    node_t prev;
    node_t next;
}nodeADT;

static void set_next_process();

//LISTA DE NODOS CIRCULAR PARA LOS PROCESOS
//TODO PROCESO SE AGREGA AL FINAL, SIGUIENDO EL ALGORITMO ROUND ROBIN
static node_t current_process;
static node_t last_process;
static size_t number_of_processes;

void init_scheduler(){
    current_process = NULL;
    last_process = NULL;
    number_of_processes = 0;
}

void run_process(process_t process){
    number_of_processes++;
    if(last_process == NULL){
        last_process = mem_alloc(sizeof(nodeADT));
        last_process->element = process;
        last_process->next = last_process;
        last_process->prev = last_process;
        current_process = last_process;
        _change_process(process->stack_pointer);
    }
    else{
        node_t aux = mem_alloc(sizeof(nodeADT));
        aux->element = process;
        aux->next = last_process->next;
        aux->prev = last_process;
        last_process->next->prev = aux;
        last_process->next = aux;
        last_process = aux;
    }
}

void kill_process(){

    number_of_processes--;

    node_t aux = current_process;
    current_process->prev->next = current_process->next;
    current_process->next->prev = current_process->prev;

    if(last_process == aux){
        last_process = aux->prev;
    }

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

void print_current_processes(){
    node_t aux = current_process;
    for(int i = 0; i < number_of_processes; i++){
        print_process(aux->element);
        aux = aux->next;
    }
}