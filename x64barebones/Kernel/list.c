#include <list.h>

typedef struct nodeADT *node_t;

typedef struct nodeADT{
    unsigned int index;
    unsigned int size;
    void *element;
    node_t next;
}nodeADT;

typedef struct listADT{
    node_t head;
    int size;
}listADT;

static int copyElement(void *buffer, void *element, unsigned int elementSize);

list_t newList() {
	list_t list = mem_alloc(sizeof(struct listADT));
	list->head = NULL;
	list->size = 0;
	return list;
}

int addElement(list_t list, const void *element, const unsigned int size) {

	if(list == NULL) return NULL_LIST_ERROR;
    if(element == NULL) return NULL_ELEMENT_ERROR;
    if(size == 0)  return SIZE_ERROR;

	node_t newNode = (node_t) mem_alloc(sizeof(nodeADT));
    newNode->element = mem_alloc(size);
    newNode->size = size;
    newNode->next = NULL;
    memcpy(newNode->element,element,size);

	node_t aux;
	if(list->head == NULL) {
        list->head = newNode;
        newNode->index = 0;
    }
    else {
		aux = list->head;
		while(aux->next != NULL) {
			aux = aux->next;
		}

        newNode->index = aux->index + 1;
		aux->next = newNode;
    }

    list->size++;
    return INSERTION_OK;
}

int getElementOnIndex(list_t list,void *buffer,const unsigned int index) {
    node_t aux;

	if(list == NULL) {
		return NULL_LIST_ERROR;
	}
    if(list->head == NULL) return EMPTY_LIST_ERROR;

	aux = list->head;
    while((aux->next != NULL) && (aux->index < index))	aux = aux->next;

    if((aux->next == NULL) || (aux->index != index)) return ELEMENT_DOESNT_EXIST;

    return copyElement(buffer,aux->element,aux->size);
}

int getFirstElement(list_t list, void * buffer) {

	if(list == NULL) {
		return NULL_LIST_ERROR;
	}

    	if(list->head == NULL) {
    		return EMPTY_LIST_ERROR;
    	}

	return copyElement(buffer,list->head->element,list->head->size);
}

int removeFirst(list_t list) {
	if(list == NULL) return NULL_LIST_ERROR;
	if(list->head == NULL) return EMPTY_LIST_ERROR;

	node_t aux;
	aux = list->head;
	list->head = list->head->next;
	free_mem(aux);
	list->size--;
	return REMOTION_OK;
}

int removeAndFreeFirst(list_t list) {
	if(list == NULL) return NULL_LIST_ERROR;
	if(list->head == NULL) return EMPTY_LIST_ERROR;

	node_t aux;
	aux = list->head;
	list->head = list->head->next;
	free_mem(aux->element);
	free_mem(aux);
	list->size--;
	return REMOTION_OK;
}

int size(list_t list) {
	if(list == NULL) return NULL_LIST_ERROR;
	return list->size;
}

int contains(list_t list, int (*compareTo)(const void*, const void*), const void *reference) {
	if(list == NULL) return FALSE;
	if(compareTo == NULL) return FALSE;

	node_t aux;
	if(list->head == NULL){
		return FALSE;
	}else {
		aux = list->head;
		while(aux != NULL){
			if((*compareTo)(reference, aux->element) == 0)	return TRUE;
			aux = aux->next;
		}
	}
	return FALSE;
}

int getFirstElementByCriteria(list_t list, int (*compareTo)(const void*, const void*), const void *reference,void *buffer) {
	if(list == NULL) return NULL_LIST_ERROR;
	if(compareTo == NULL) return NULL_FUNCTION_POINTER;

	node_t aux;
	if(list->head == NULL) {
		return ELEMENT_DOESNT_EXIST;
	}else {
		aux = list->head;
		while (aux != NULL) {
			if((*compareTo)(reference, aux->element) == 0) {
				return copyElement(buffer,aux->element,aux->size);
			}
            aux = aux->next;
		}
	}
	return ELEMENT_DOESNT_EXIST;
}

void *getFirstElementReferenceByCriteria(list_t list,
	int (*compareTo)(const void * , const void * ), const void *reference) {

	if(list == NULL) return NULL;
	if(compareTo == NULL) return NULL;

	node_t aux = list->head;
	while (aux != NULL) {
		if((*compareTo)(reference,aux->element) == 0) {
			return aux->element;
		}
        aux = aux->next;
	}
	return NULL;
}

int removeAndFreeFirstElementByCriteria(list_t list,
	int (*compareTo)(const void * , const void  *), const void *reference) {

	node_t aux;
	node_t auxPrev;
	node_t aux2;
	int firstLoop = 1;
	if(list == NULL) return NULL_LIST_ERROR;
	if(compareTo == NULL) return NULL_FUNCTION_POINTER;
	if(list->head == NULL) {
		return ELEMENT_DOESNT_EXIST;
	}else {
		aux = list->head;
		auxPrev=NULL;

		while (aux != NULL) {
			if((*compareTo)(reference,aux->element) == 0) {
                list->size--;
				aux2 = aux->next;
				free_mem(aux->element);
				free_mem(aux);
				if(firstLoop == 1){
					list->head = aux2;
				}else {
					auxPrev->next = aux2;
				}
				return REMOTION_OK;
			}
			auxPrev = aux;
			aux = aux->next;
			firstLoop = 0;
		}
		return ELEMENT_DOESNT_EXIST;
	}
}

int removeFirstElementByCriteria(list_t list,int (*compareTo)(const void * , const void * ),
															const void *reference) {
	node_t aux;
	node_t auxPrev;
	node_t aux2;
	int firstLoop = 1;
	if(list == NULL) return NULL_LIST_ERROR;
	if(compareTo == NULL) return NULL_FUNCTION_POINTER;
	if(list->head == NULL) {
		return ELEMENT_DOESNT_EXIST;
	}else {
		aux = list->head;
		auxPrev=NULL;

		while (aux != NULL) {
			if((*compareTo)(reference,aux->element) == 0) {
                list->size--;
				aux2 = aux->next;
				free_mem(aux);
				if(firstLoop == 1){
					list->head = aux2;
				}else {
					auxPrev->next = aux2;
				}
				return REMOTION_OK;
			}
			auxPrev = aux;
			aux = aux->next;
			firstLoop = 0;
		}
		return ELEMENT_DOESNT_EXIST;
	}
}

int removeAndFreeAllElements(list_t list) {
	if(list == NULL) return NULL_LIST_ERROR;
	while (removeAndFreeFirst(list) != EMPTY_LIST_ERROR);
	return REMOTION_OK;
}

int removeAllElements(list_t list) {
	if(list == NULL) return NULL_LIST_ERROR;
	while (removeFirst(list) != EMPTY_LIST_ERROR);
	return REMOTION_OK;
}

static int copyElement(void *buffer,void *element,unsigned int elementSize) {
	memcpy(buffer, element, elementSize);
	return elementSize;
}

void *getFirstElementReferece(list_t list) {
	if(list == NULL) return NULL;
	if(list->head == NULL) return NULL;
	return list->head->element;
}

void freeList(list_t list) {
	free_mem(list);
}