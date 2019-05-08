#include "include/mutex_test.h"

static int value = 1;
static int x = 0;

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
    sys_lock();
    x++;
    print_f("Value of x: %d \n", x);
    sys_unlock();
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
    // char ids[50];
    // for(int i = 0; i < 50; i++){
    //     ids[i] = i + '0';
    // }
    for(int i = 0; i < 10;i++){
        sys_create_process(variable_lock_test, "TEST");
    }
    sys_print_all_procceses();
}
