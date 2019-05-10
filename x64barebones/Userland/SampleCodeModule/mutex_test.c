#include "include/mutex_test.h"

static int x;

void variable_lock_test(){
    for(int i = 0; i < 1000; i++){
    sys_lock();
    x++;
    sys_unlock();
    }
}

void mutex_test(){
    x = 0;
    sys_create_process(variable_lock_test, "M_TEST1", BACKGROUND);
    sys_create_process(variable_lock_test, "M_TEST2", BACKGROUND);
    sys_print_all_procceses();
    sys_sleep(10);
    print_f("Should be 2000 : %d \n", x);
}
