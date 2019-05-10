#include <mutex.h>

void lock_mutex(void * lock){
    _spin_lock((uint64_t)lock);
}

void unlock_mutex(void * lock){
    _spin_unlock((uint64_t)lock);
}