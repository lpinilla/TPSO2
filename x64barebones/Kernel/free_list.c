#include <free_list.h>

void initialize_list(void * start_ptr, size_t total_size){        
    n_of_nodes = 1;
    struct t_Node first_node = {.next = NULL, .prev = NULL,
                                .mem_ptr = (void *) (size_t) start_ptr + sizeof(struct t_Node),
                                .size = total_size,
                                .status = F};
    root = last = start_ptr;
    memcpy(start_ptr, &first_node, sizeof(struct t_Node));
    start_dir = start_ptr;
    total_mem_size = total_size;
}

Node add_node(void * node_location, size_t size){ 
    if(size == 0 || node_location == NULL){
        return NULL;
    }
    struct t_Node n_node = {.next = NULL, .prev = last,
                            .mem_ptr = (void *) node_location + sizeof(struct t_Node),
                            .size = size - sizeof(struct t_Node),
                            .status = F};
    n_node.prev = last;
    last = node_location;
    n_of_nodes++;
    memcpy(node_location, &n_node, sizeof(struct t_Node));
    return (Node) node_location;
}

Node find_first_fit(Node curr, size_t size){
    if(curr == NULL || size == 0){return NULL;}
    if(curr->status == F && curr->size == size){
        curr->status = P;
        return curr->mem_ptr;
    }
    if(curr->status == F && (curr->size > size)){
        curr->status = P;
        size_t dif = curr->size - size;
        //si el espacio que sobra es suficiente, aloca un nuevo nodo
        if(dif >= sizeof(struct t_Node)){
            curr->size = size;
            curr->next = add_node(curr->mem_ptr + size, dif);        
        }
        return curr->mem_ptr;
    }
    return curr->next = find_first_fit(curr->next, size);
}

Node free_mem(Node curr, void * mem_ptr){ //TODO:revisar bien los casos si prev o next son null
    if(curr == NULL || mem_ptr == NULL) return NULL; //tal vez separar caso de error
    if(curr->mem_ptr == mem_ptr){ //encontramos el puntero a liberar
        //4 casos de liberación, ver libro de Tanenbaum 4ta edición
        if((curr->prev == NULL || curr->prev->status == P) && (curr->next == NULL || curr->next->status == P)){
            curr->status = F;
            return curr;
        }else if((curr->prev != NULL && curr->prev->status != P) && (curr->next == NULL || curr->next->status == P)){
            //caso libre izq -> se agranda izq
            curr->prev->size = curr->size + sizeof(struct t_Node);
            curr->next->prev = curr->prev;
            return curr->next;
        }else if((curr->prev == NULL || curr->prev->status == P)  && (curr->next == NULL && curr->next->status != P)){
            //caso libre der -> me agrando yo
            curr->status = F;
            curr->size = curr->next->size + sizeof(struct t_Node);
            curr->next = curr->next->next;
            curr->next->next->prev = curr;
            return curr;
        }else if((curr->prev != NULL && curr->prev->status != P)  && (curr->next != NULL && curr->next->status != P)){
            //caso libre de ambos lados -> me agrando yo y después se agranda izq
            curr->prev->size = curr->size + curr->next->size + 2 * sizeof(struct t_Node);
            curr->next->next->prev = curr->prev;
            return curr->next->next;
        }
        return curr->next = free_mem(curr->next, mem_ptr);
    }
}
