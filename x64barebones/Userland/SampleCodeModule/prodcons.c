#include <prodcons.h>
#include <stdint.h>
#include "include/syscall.h"
#include "include/utilities.h"

static int lock;
static int sem;
static int buffer;
static int producers[MAX_PRODUCERS];
static int consumers[MAX_CONSUMERS];
static int producers_size;
static int consumers_size;
static int printer_pid;

static void producer();
static void consumer();
static void printer();
static void terminate_last_producer();
static void terminate_last_consumer();

static void producer(){
    while(1){
        sys_lock(&lock);
        buffer++;
        sys_sem_post(sem);
        sys_unlock(&lock);
    }
}

static void consumer(){
    while(1){
        sys_sem_wait(sem);
        sys_lock(&lock);
        buffer--;
        sys_unlock(&lock);
    }
}

static void printer(){
    while(1){
        sys_clear_console();
        print_f("Press p to create producer.\n");
        print_f("Press c to create consumer.\n");
        print_f("Press o to terminate producer.\n");
        print_f("Press x to terminate consumer.\n");
        print_f("Press q to quit prodcons.\n");
        sys_print_all_procceses();
    }
}

static void terminate_last_producer(){
    if(producers_size > 0){
        sys_kill_process(producers[--producers_size]);
    }
}

static void terminate_last_consumer(){
    if(consumers_size > 0){
        sys_kill_process(consumers[--consumers_size]);
    }
}

void prodcons(){
    char c;
    char * producer_name = "PRODUCER-N";
    char * consumer_name = "CONSUMER-N";
    int running = 1;

    lock = 0;
    sem = sys_sem_open("prodcons");
    sys_sem_wait(sem);
    buffer = 0;
    consumers_size = 0;
    producers_size = 0;
    printer_pid = sys_create_process(printer, "PRINTER", FOREGROUND);

    while(running){
        c = get_char();
        switch(c){
            case 'p':
                if(producers_size < MAX_PRODUCERS){
                    producer_name[9] = (char)(producers_size + 1 + '0');
                    producers[producers_size] = sys_create_process(producer, producer_name, BACKGROUND);
                    producers_size++;
                }
                break;
            case 'c':
                if(consumers_size < MAX_CONSUMERS){
                    consumer_name[9] = (char)(consumers_size + 1 + '0');
                    consumers[consumers_size] = sys_create_process(consumer, consumer_name, BACKGROUND);
                    consumers_size++;
                }
                break;
            case 'o':
                terminate_last_producer();
                break;
            case 'x':
                terminate_last_consumer();
                break;
            case 'q':
                running = 0;
                while(producers_size > 0){
                    terminate_last_producer();
                }
                while(consumers_size > 0){
                    terminate_last_consumer();
                }
                sys_kill_process(printer_pid);
                sys_sem_close(sem);
                break;
        }
    }
}