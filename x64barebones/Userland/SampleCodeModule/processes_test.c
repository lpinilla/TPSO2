#include "include/processes_test.h"

void child1_process(){
	print_f("Process 1\n");
    while(1){

    }
}

void child2_process(){
    print_f("Process 2\n");
	while(1){
        
    }
}

void process_test(){

	int child1 = sys_create_process(child1_process, "First Child Process");
	int child2 = sys_create_process(child2_process, "Second Child Process");
    sys_beep();
	print_f("Current Processes: \n");
    sys_print_all_procceses();

    print_f("Killing process %d\n", child1);
    sys_kill_process(child1);
    sys_beep();
    print_f("Current Processes: \n");
    sys_print_all_procceses();

    print_f("Killing process %d\n", child2);
    sys_kill_process(child2);
    sys_beep();
    print_f("Current Processes: \n");
    sys_print_all_procceses();
}
