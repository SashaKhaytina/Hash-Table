#ifndef LIST_H
#define LIST_H

#include <stdio.h>

#include "common.h"


typedef struct Node Node;
struct Node 
{
    Elem_t value;
    Node* next;
    Node* parent;
};


typedef struct List List;
struct List
{
    Node* root;
    size_t size;
};



TestStatus list_ctor(List* list);
List*      list_dtor(List* list);

TestStatus list_push  (List* list, Elem_t elem);
TestStatus list_delete(List* list, Elem_t elem);

Node* list_find(List list, Elem_t element);


void list_print(const List* list);

#endif
