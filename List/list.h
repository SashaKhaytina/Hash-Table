#ifndef LIST_COMMANDS_H
#define LIST_COMMANDS_H

#include "../common.h"


#ifdef TESTNUM
#define POISON_ELEM_LIST -1
#else
#define POISON_ELEM_LIST "\0"
#endif


typedef struct Node Node;
struct Node 
{
    Elem_t value;
    int next;
    int prev;    
};

typedef struct List List;
struct List
{
    Node* array;
    size_t size;
    int ind_first_free_node;    // ind first free cell
};


TestStatus list_ctor(List* list);
List*      list_dtor(List* list);

TestStatus list_push         (List* list, Elem_t elem, int ind);    // ind - на какой индекс ХОТИМ ПОСТАВИТЬ
TestStatus list_delete       (List* list, Elem_t elem);
TestStatus list_delete_by_ind(List* list, int ind);                 // ind - с какого индекса ХОТИМ УДАЛИТЬ    

int        list_find  (List* list, Elem_t element);                 // return ind in array

void       list_print (const List* list);

#endif