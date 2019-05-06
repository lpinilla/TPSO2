#include <ipc.h>

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
}

void my_read(int rpid, char * ret){
    int found = 0;
    found++; //para que compile -> BORRAR
    //sem_wait(sem);    //esperar al semáforo a qué haya algo para leer
    lock_mutex();   //ganar el recurso
    for(int i = 0; i < MAX_MESSAGES; i++){
        //ver si el mensaje es para un pid que esta vivo
        if(mailbox[i].rpid == rpid){
            memcpy(ret, mailbox[i].msg, strlen2(mailbox[i].msg));
            mailbox[i].seen = 1;
            break;
        }
    }
    //if(!found) sem_post(sem); //decrementar el semáforo número si se leyó
    unlock_mutex();    //liberar el recurso
}

void * get_mailbox_address(){
    return mailbox;
}