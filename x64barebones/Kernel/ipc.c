#include "./include/ipc.h"
#include "./include/mem_manager.h"
#include "./include/lib.h"
#include <stdio.h>

void init_mailbox(){
    mailbox_index = 0;
    memset(mailbox, 0, sizeof(t_Message) * MAX_MESSAGES);
}

void my_write(char * msg, int rpid, int spid){
    int mid = 0;
    //creamos la estructura
    t_Message n_msg = {.rpid = rpid, .spid = spid, .mid = mid, .seen = 0};
    if(n_msg.msg == NULL) n_msg.msg = mem_alloc(MAX_NAME_SIZE * sizeof(char));
    memcpy(n_msg.msg, msg, strlen2(msg));
    //ver si puedo escribir un mensaje en la memoria (lock)
    //si semáforo = MAX_MESSAGES, bloquear
    //escribir
    mailbox[mailbox_index++] = n_msg;
    //incrementar semáforo
}

void my_write2(char * msg, int rpid, int spid){
    //mutex lock

    //mutex unlock
}


void my_read(int rpid, char * ret){
    int found = 0;
    found++; //para que compile
    //sem_wait(sem);    //esperar al semáforo a qué haya algo para leer
    //read_mutex_lock   //ganar el recurso
    for(int i = 0; i < MAX_MESSAGES; i++){
        if(mailbox[i].rpid == rpid){
            if(!strcmp2(mailbox[i].msg, "ACK")){ //retornarle al write
                found = 1;
                mailbox[i].seen = 1;
                break;
            }
            //cambiamos el mensaje para enviar un ACK al escritor
            int aux = mailbox[i].rpid;            
            char * ack = "ACK";
            mailbox[i].rpid = mailbox[i].spid;
            mailbox[i].spid = aux;
            memcpy(ret, mailbox[i].msg, strlen2(mailbox[i].msg));
            memcpy(mailbox[i].msg, ack, 4);
            break;
        }
    }
    //if(!found) sem_post(sem); //decrementar el semáforo número si se leyó
    //read_mutex_unlock;    //liberar el recurso para otros read
}

void * get_mailbox_address(){
    return mailbox;
}