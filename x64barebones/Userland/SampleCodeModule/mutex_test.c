#include "include/mutex_test.h"

static int value = 0;

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

void mutex_child1_process(){
    mutex_child_action();
}

void mutex_child2_process(){
    mutex_child_action();
}

void mutex_test(){

	sys_create_process(mutex_child1_process, "First Child Process");
	sys_create_process(mutex_child2_process, "Second Child Process");

	print_f("Current Processes: \n");
    sys_print_all_procceses();

}
