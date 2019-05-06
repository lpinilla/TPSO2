#ifndef _IPC_H_
#define _IPC_H_

#include <stdint.h>
#include <mem_manager.h>
#include <lib.h>
#include <mutex.h>
#include <semaphore.h>

#define MAX_MESSAGES 100
#define MAX_MESSAGE_SIZE 256

typedef struct{
    int rpid, spid, mid, seen;
    char * msg;
}t_Message;

typedef t_Message * Message;

t_Message mailbox[MAX_MESSAGE_SIZE];

int mailbox_index; 

#endif