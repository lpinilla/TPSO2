#ifndef _MEM_MANAGER_H_
#define _MEM_MANAGER_H_

#include <stddef.h>
#include <string.h>

enum STATUS {P = 0, F = 1};

struct t_Node{ 
    struct t_Node * next, *prev;
    void * mem_ptr;
    size_t size;
    enum STATUS status;
};

typedef struct t_Node * Node;

void * start_dir;

Node root, last;
size_t total_mem_size;


/*función para inicializar la memoria dado un puntero inicial y el tamaño
**total de la memoria*/
void initialize_list(void * start_ptr, size_t total_size);

/*función para agregar un nodo nuevo a la lista de alocación*/
Node add_node(void * node_location, size_t size);

/*función que implementa first fit en la lista de alocación,
**si el espacio que encuentra es más grande que el pedido y hay espacio
**para crear un nuevo nodo, crea un nuevo nodo que apunta a la nueva zona
**de memoria liberada y lo agrega a la lista*/
Node find_first_fit(Node curr, size_t size);

/*función que llama a find_first_fit con el nodo raíz y 
**retorna el puntero del nodo adecuado*/
void * mem_alloc(size_t size);

//función que llama a liberar el nodo que tenga el puntero apuntando a ptr
void free_mem(void * ptr);

//función para liberar un nodo de la lista (de ser necesario, elimilandolo) 
Node free_node(Node curr, void * mem_ptr);

#endif

