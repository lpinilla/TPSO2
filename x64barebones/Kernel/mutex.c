#include <mutex.h>

void lock_mutex(){
    process_t current_process = get_current_process();
    pstate_t current_process_state = get_state(current_process);
    if(current_process_state == P_RUNNING || current_process_state == P_READY){
        set_state(current_process, P_CRITICAL);
    }
}

void unlock_mutex(){
    process_t current_process = get_current_process();
    if(get_state(current_process) == P_CRITICAL){
        set_state(current_process, P_RUNNING);
    }
}