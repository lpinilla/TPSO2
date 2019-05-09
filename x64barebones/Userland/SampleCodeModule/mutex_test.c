#include "include/mutex_test.h"

static int value = 1;
static int x = 0;
int y = 0;

void mutex_child1_process();
void mutex_child2_process();
void mutex_child_action();
 
void mutex_child_action(){ 
    sys_lock();
    
    value++;
    print_f("Process %d has started\n", value); 
  
    for(int i=0; i<100000;i++); 
    
    print_f("Process %d has finished\n", value); 
  
    sys_unlock(); 
} 

void variable_lock_test(){
    for(int i = 0; i < 1000; i++){
    sys_lock();
    x++;
    sys_unlock();
    }
}

void mutex_child1_process(){
    mutex_child_action();
}

void mutex_child2_process(){
    mutex_child_action();
}

/*void mutex_test(){
    for(int i = 0; i < 100; i++){
        sys_create_process(mutex_child_action, i + '0');
    }
	print_f("Current Processes: \n");
    sys_print_all_procceses();
}*/

void mutex_test(){
    sys_create_process(variable_lock_test, "TEST1",0);
    sys_create_process(variable_lock_test, "TEST2",0);
    sys_print_all_procceses();
    print_f("should be 2000: %d \n", x);
}
