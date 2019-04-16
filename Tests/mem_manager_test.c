#include "../Tasteful/testing_suite.h"
#include "../x64barebones/Kernel/include/mem_manager.h"

//ver si se inicializa bien la lista
void initialize_test();
void alloc_test();
void no_space_test();
//alocar espacio para 10 procesos y ver que rechaza un nuevo
void multiple_alloc_no_space();
void free_test();
void multiple_alloc_with_free();

int main(void){
    create_suite("Testing the Memory Manager");
    //agregando los tests
    add_test(initialize_test);
    add_test(alloc_test);
    add_test(no_space_test);
    add_test(multiple_alloc_no_space);
    add_test(free_test);
    add_test(multiple_alloc_with_free);
    //correr la suite
    run_suite();
    //liberar los espacios
    clear_suite();
}

void initialize_test(){
    size_t size = 100;
    void * mem = malloc(size);
    int ret = 0;
    if(mem == NULL) exit(EXIT_FAILURE);
    initialize_list(mem, size);
    //revisar que esta la estructura creada
    struct t_Node expected = {.next = NULL, .prev = NULL,
                     .mem_ptr = (void *) ((char *) mem + sizeof(struct t_Node)),
                     .size = size,
                     .status = F};
    Node result = (Node) mem;
    ret = (result->next == expected.next) && (result->prev == expected.prev) 
        && (result->mem_ptr == expected.mem_ptr) && (result->size == expected.size)
        && (result->status == expected.status); 
    free(mem);
    assert_true(ret);
}

void alloc_test(){
    size_t mem_size = 100;
    void * mem = malloc(mem_size * mem_size), * aux = NULL;
    int ret = 0;
    initialize_list(mem, mem_size * mem_size);
    if(mem == NULL) exit(EXIT_FAILURE);    
    aux = mem_alloc(mem_size);
    ret = aux != NULL;
    free(mem);
    assert_true(ret);
}

void no_space_test(){
    size_t mem_size = 100;
    void * mem = malloc(mem_size * mem_size), * aux = NULL;
    int ret = 0;
    initialize_list(mem, mem_size);
    if(mem == NULL) exit(EXIT_FAILURE);
    aux = mem_alloc(mem_size - sizeof(struct t_Node));
    if(aux == NULL) exit(EXIT_FAILURE);
    aux = mem_alloc(1);
    ret = aux == NULL;
    free(mem);
    assert_true(ret);
}

void multiple_alloc_no_space(){
    size_t total_size = 100;
    void * mem = malloc(total_size * total_size), * aux = NULL, * last = NULL;
    int ret = 0;
    if(mem == NULL) exit(EXIT_FAILURE);
    initialize_list(mem, 2 * total_size);
    for(int i = 0; i < 2; i++){
        aux = mem_alloc(60);
        if(aux == NULL) exit(EXIT_FAILURE);
    }
    //proceso que no se podría alocar    
    last = mem_alloc(1);
    ret = last == NULL;
    free(mem);
    assert_true(ret);
}

void free_test(){
    size_t total_size = 100;
    void * mem = malloc(total_size * total_size), * aux = NULL;
    int ret = 0;
    if(mem == NULL) exit(EXIT_FAILURE);
    initialize_list(mem, total_size * total_size);
    aux = mem_alloc(total_size);
    if(aux == NULL) exit(EXIT_FAILURE);
    free_mem(aux);
    aux = mem_alloc(1);
    ret = aux != NULL;
    free(mem);
    assert_true(ret);
}

void multiple_alloc_with_free(){
    size_t total_size = 100;
    void * mem = malloc(total_size * total_size), * aux = NULL, * last = NULL;
    int ret = 0;
    if(mem == NULL) exit(EXIT_FAILURE);
    initialize_list(mem, total_size * total_size);
    for(int i = 0; i < 10; i++){
        aux = mem_alloc(total_size / 10);
        if(aux == NULL) exit(EXIT_FAILURE);
    }
    free_mem(aux);
    //proceso que no se podría alocar
    last = mem_alloc(1);
    ret = last != NULL;
    free(mem);
    assert_true(ret);
}