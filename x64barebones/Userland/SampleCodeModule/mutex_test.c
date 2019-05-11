#include "include/mutex_test.h"

static int x;
static int lock;

void variable_lock_test(){
    while(x < 10000){
        sys_lock(&lock);
        x++;
        sys_unlock(&lock);
    }
}

void mutex_test(){
    x = 0;
    lock = 0;
    sys_create_process(variable_lock_test, "M_TEST1", BACKGROUND);
    sys_create_process(variable_lock_test, "M_TEST2", BACKGROUND);
    sys_create_process(variable_lock_test, "M_TEST3", BACKGROUND);
    sys_create_process(variable_lock_test, "M_TEST4", BACKGROUND);
    sys_create_process(variable_lock_test, "M_TEST5", BACKGROUND);
    sys_print_all_procceses();
    sys_sleep(10);
    print_f("Should be 10000 : %d \n", x);
}
