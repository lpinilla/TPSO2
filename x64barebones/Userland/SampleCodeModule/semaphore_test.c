#include "include/semaphore_test.h"

static int sem;

void sem_child1_process();
void sem_child2_process();
void sem_child3_process();

void sem_child1_process(){
    sys_sem_wait(sem);
    print_f("Sem Consumed from First Child\n");
    print_f("Sem Post from First Child\n");
    sys_sem_post(sem);
    print_f("Sem Post from First Child\n");
    sys_sem_post(sem);
}

void sem_child2_process(){
    sys_sem_wait(sem);
    print_f("Sem Consumed from Second Child\n");
}

void sem_child3_process(){
    sys_sem_wait(sem);
    print_f("Sem Consumed from Third Child\n");
}

void semaphore_test(){

    sem = sys_sem_open("Sem Test");
	sys_create_process(sem_child1_process, "First Child Process", 1);
	sys_create_process(sem_child2_process, "Second Child Process", 0);
    sys_create_process(sem_child3_process, "Third Child Process", 0);

	print_f("Current Processes: \n");
    sys_print_all_procceses();
}