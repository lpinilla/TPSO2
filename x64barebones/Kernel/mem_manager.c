//incluirlo manualmente para los tests
#include "./include/mem_manager.h"
#include "./include/graphics.h"

void * start_dir;

Node root, last;
size_t total_mem_size;

void initialize_list(void * start_ptr, size_t total_size){
    struct t_Node first_node = {.next = NULL, .prev = NULL,
                                .mem_ptr = (void *) ((char *) start_ptr + sizeof(struct t_Node)),
                                .size = total_size,
                                .status = F};
    root = last = start_ptr;
    memcpy(start_ptr, &first_node, sizeof(struct t_Node));
    start_dir = start_ptr;
    total_mem_size = total_size;
}

void * return_memory_base(){
    return start_dir;
}

Node add_node(void * node_location, size_t size){ 
    if(size == 0 || node_location == NULL){
        return NULL;
    }
    struct t_Node n_node = {.next = NULL, .prev = last,
                            .mem_ptr = (void *) ((char *)node_location + sizeof(struct t_Node)),
                            .size = size - sizeof(struct t_Node),
                            .status = F};
    n_node.prev = last;
    last = node_location;
    memcpy(node_location, &n_node, sizeof(struct t_Node));
    return (Node) node_location;
}



Node find_first_fit(Node curr, size_t size){
    if(curr == NULL || size == 0) return NULL;
    if(curr->status == F && curr->size == size){
        curr->status = P;
        return curr;
    }
    if(curr->status == F && (curr->size > size)){
        curr->status = P;
        size_t dif = curr->size - size;
        //si el espacio que sobra es suficiente, aloca un nuevo nodo
        if(dif >= sizeof(struct t_Node)){
            curr->size = size;
            curr->next = add_node(curr->mem_ptr + size, dif);        
        }
        return curr;
    }
    return find_first_fit(curr->next, size);
}


void * mem_alloc(size_t size){
    Node ret = find_first_fit(root, size);
    if(ret == NULL) return NULL;
    return ret->mem_ptr;
}


void free_mem(void * ptr){
    root = free_node(root, ptr);
    if(root == NULL){
        //ncPrint("Error liberando, mal puntero indicado");
    }
}


Node free_node(Node curr, void * mem_ptr){
    if(curr == NULL || mem_ptr == NULL) return NULL; //tal vez separar caso de error
    if(curr->mem_ptr == mem_ptr){ //encontramos el puntero a liberar
        //4 casos de liberación y merge, ver libro de Tanenbaum 4ta edición
        if((curr->prev == NULL || curr->prev->status == P) && (curr->next == NULL || curr->next->status == P)){
            //caso ambos ocupados
            curr->status = F;
            return curr;
        }else if((curr->prev != NULL && curr->prev->status != P) && (curr->next == NULL || curr->next->status == P)){
            //caso libre izq -> se agranda izq
            curr->prev->size += curr->size + sizeof(struct t_Node);
            if(curr->next != NULL) curr->next->prev = curr->prev;
            return curr->next;
        }else if((curr->prev == NULL || curr->prev->status == P)  && (curr->next != NULL && curr->next->status != P)){
            //caso libre der -> me agrando yo
            curr->status = F;
            curr->size += curr->next->size + sizeof(struct t_Node);
            if(curr->next->next != NULL) curr->next->next->prev = curr;
            curr->next = curr->next->next;            
            return curr;
        }else if((curr->prev != NULL && curr->prev->status != P)  && (curr->next != NULL && curr->next->status != P)){
            //caso libre de ambos lados -> se agranda la izq el tamaño mío más el de la derecha
            curr->prev->size += curr->size + curr->next->size + 2 * sizeof(struct t_Node);
            if(curr->next->next != NULL){
                curr->next->next->prev = curr->prev;
                return curr->next->next;
            }
            return NULL;
        }
    }
    curr->next = free_node(curr->next, mem_ptr);
    return curr;
}

/*void print_list(){
    print_r_list(root);
}

void print_r_list(Node curr){
    if(curr == NULL) return;
    draw_string("mem_ptr:");
    draw_number((uint64_t) curr->mem_ptr);
    draw_string(" status");
    draw_number(curr->status);
    draw_string(" size");
    draw_number(curr->size);
    draw_string("\n");
    print_r_list(curr->next);
}*/
