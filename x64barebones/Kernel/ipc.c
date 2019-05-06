#include "./include/ipc.h"
#include "./include/mem_manager.h"
#include "./include/lib.h"
#include <stdio.h>

void init_mailbox(){
    mailbox_index = 0;
    memset(mailbox, 0, sizeof(t_Message) * MAX_MESSAGES);
}

void my_write(char * msg, int rpid, int spid){
    int mid = 0, free_spot = 0;
    //vemos si podemos escribir
    //if semaforo == MAX_MESSAGES -> block;
    //writer_mutex_lock //adquirimos el permiso de escribir
    //encontrar el 1er espacio libre
    for(int i = 0; i < MAX_MESSAGES; i++){
        if((mailbox[i].spid == 0 && mailbox[i].rpid == 0) || mailbox[i].seen == 1){
            free_spot = i;
            break;
        } 
    }
    mailbox[free_spot].mid = mid;
    mailbox[free_spot].rpid = rpid;
    mailbox[free_spot].spid = spid;
    mailbox[free_spot].seen = 0;
    if(mailbox[free_spot].msg == NULL){
        mailbox[free_spot].msg = (char *)  mem_alloc(MAX_MESSAGE_SIZE * sizeof(char));
    }
    str_cpy(msg, mailbox[free_spot].msg); //copiamos el mensaje a la estructura
    //sem_post(sem) sumarle al semáforo para indicar que hay un mensaje disponible
    //writer_mutex_unlock
    my_read(spid, NULL); //podemos hacer que si no llega el mensaje, se reenvíe.
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