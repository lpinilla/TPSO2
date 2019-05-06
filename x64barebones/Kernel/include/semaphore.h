#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#include <stdint.h>
#include <process.h>
#include <scheduler.h>
#include <mem_manager.h>
#include <lib.h>

#define MAX_SEMAPHORES 128
#define MAX_SEMAPHORE_NAME 256

int my_sem_open(char * name);
int my_sem_close(int sid);
int my_sem_post(int sid);
int my_sem_wait(int sid);
void my_sem_print(int sid);

#endif