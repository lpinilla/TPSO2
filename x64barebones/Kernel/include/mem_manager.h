#ifndef _MEM_MANAGER_H_
#define _MEM_MANAGER_H_

#include <stddef.h>

/*función para inicializar la memoria dado un puntero inicial y el tamaño
**total de la memoria*/
void initialize_list(void * start_ptr, size_t total_size);

/*función que llama a find_first_fit con el nodo raíz y 
**retorna el puntero del nodo adecuado*/
void * mem_alloc(size_t size);

//función que llama a liberar el nodo que tenga el puntero apuntando a ptr
void free_mem(void * ptr);

//devuelve un puntero al inicio de la memoria
void * return_memory_base();

void print_list();

#endif