#include "../Tasteful/testing_suite.h"
#include "../x64barebones/Kernel/include/mem_manager.h"
#include "../x64barebones/Userland/SampleCodeModule/include/call_int_80.h"
#include "../x64barebones/Userland/SampleCodeModule/include/mem_manager.h"

void malloc_test();

int main(void){
    create_suite("Testing the Memory Manager");
    //agregando los tests
    add_test(malloc_test);
    //correr la suite
    run_suite();
    //liberar los espacios
    clear_suite();
}

//test que traté de hacer para ver si desde userland funcionaba "conectarse" a la memoria
void malloc_test(){
    //init memory
    void * mem = malloc(1000);
    char * ptr = NULL;
    size_t mem_size = 1000;
    if(mem == NULL) exit(EXIT_FAILURE);
    initialize_list(mem, mem_size);     //importante llamar a que el kernel inicialice la memoria
    //----kernel
    //user
    ptr = (char *) my_malloc(mem_size / 100);
    if(ptr == NULL) exit(EXIT_FAILURE);
    printf("todo ok \n");
    printf("%p \n", mem);
    printf("%p \n", ptr);
    for(int i = 0; i < 10; i++){
        printf("quiero printear\n");
        ptr[i] = i + '0';
    }
    printf("todo ok2 \n");
    //checkear que de verdad se escribió eso
    int ret = 0;
    for(int i = 0; i < 10; i++){
        if(ptr[i] != (i + '0')) ret++;
    }
    my_free(ptr);
    free(mem);
    assert_true(!ret);
}