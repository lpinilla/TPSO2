#ifndef LIST_ADT
#define LIST_ADT

#define INSERTION_OK 0
#define REMOTION_OK 0
#define NULL_ELEMENT_ERROR 1
#define SIZE_ERROR 2
#define NULL_LIST_ERROR -3
#define EMPTY_LIST_ERROR -2
#define ELEMENT_DOESNT_EXIST -1
#define FALSE 0
#define TRUE 1
#define NULL_FUNCTION_POINTER -4


typedef struct listADT *list_t;

#include <string.h>
#include <lib.h>
#include <mem_manager.h>

list_t newList();

int addElement(list_t list, const void *element, const unsigned int size);

int getElementOnIndex(list_t list, void *buffer, const unsigned int index);

int getFirstElementByCriteria(list_t list,int (*compareTo)(const void * , const void * ),
                                                             const void * reference, void * buffer);

int getFirstElement(list_t list,void * buffer);

void *getFirstElementReferenceByCriteria(list_t list, int (*compareTo)(const void *, const void * ),const void *reference);

void *getFirstElementReferece(list_t list);

int size(list_t list);

int contains(list_t list, int (*compareTo)(const void * , const void * ), const void *reference);

int removeFirst(list_t list);

int removeAndFreeFirst(list_t list);

int removeFirstElementByCriteria(list_t list,int (*compareTo)(const void * , const void * ),
                                                                                const void *reference);

int removeAndFreeFirstElementByCriteria(list_t list,int (*compareTo)(const void * , const void * ),
                                                                                     const void *reference);

int removeAllElements(list_t list);

int removeAndFreeAllElements(list_t list);

void freeList();

#endif