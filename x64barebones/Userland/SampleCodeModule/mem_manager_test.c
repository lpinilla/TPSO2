#include "include/mem_manager_test.h"

void mem_manager_test(){
    sys_print_mem_list();
    for(int i = 0; i<2; i++){
        void * alloc1 = sys_my_malloc(100);
        if(alloc1 == NULL){
            print_f("1:Error\n");
            sys_print_mem_list();
            return;
        }
        print_f("ptr1 = %d\n", alloc1);
        void * alloc2 = sys_my_malloc(200);
        if(alloc2 == NULL){
            print_f("2:Error\n");
            sys_print_mem_list();
            return;
        }
        print_f("ptr2 = %d\n", alloc2);
        void * alloc3 = sys_my_malloc(300);
        if(alloc3 == NULL){
            print_f("3:Error\n");
            sys_print_mem_list();
            return;
        }
        print_f("ptr3 = %d\n", alloc3);
        print_f("before free\n");
        sys_print_mem_list();
        print_f("frees\n");
        print_f("free ptr1\n");   
        sys_my_free(alloc1);
        sys_print_mem_list();
        print_f("free ptr2\n");      
        sys_my_free(alloc2);
        sys_print_mem_list();
        print_f("free ptr3\n");   
        sys_my_free(alloc3);
        sys_print_mem_list();
    }
}
