#include "include/mem_manager_test.h"

void mem_manager_test(){
    sys_print_mem_list();
    for(int i = 0; i<3; i++){
        void * alloc1 = sys_my_malloc(100);
        if(alloc1 == NULL) print_f("1:Error\n");
        print_f("Alloc1 = %d\n", alloc1);
        void * alloc2 = sys_my_malloc(200);
        if(alloc2 == NULL) print_f("2:Error\n");
        print_f("Alloc2 = %d\n", alloc2);
        void * alloc3 = sys_my_malloc(300);
        if(alloc3 == NULL) print_f("3:Error\n");
        print_f("Alloc3 = %d\n", alloc3);
        sys_print_mem_list();
        sys_my_free(alloc1);
        sys_my_free(alloc2);
        sys_my_free(alloc3);
        sys_print_mem_list();
    }
}
