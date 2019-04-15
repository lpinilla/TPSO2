#include <memory.h>


void* my_malloc(int size){
    if(size<0){
        //bai
    }
    return sys_my_malloc(size);
}

void free(void* ptr){
    return sys_my_free(ptr);
}