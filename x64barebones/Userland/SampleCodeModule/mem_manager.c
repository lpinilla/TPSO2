#include <mem_manager.h>


void* my_malloc(int size){
    if(size<0){
        return NULL;
    }
    return sys_my_malloc(size);
}

void my_free(void* ptr){
    sys_my_free(ptr);
}