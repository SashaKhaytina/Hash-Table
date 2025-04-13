#include "list.h"

#include <stdlib.h>
#include <string.h>


static TestStatus   cut_node       (List* list, Node* delete_node);
static struct Node* create_new_node(Elem_t elem, Node* next, Node* parent, TestStatus* status);
static void         print_nodes    (const Node* node);

TestStatus list_ctor(List* list)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, list)
    TestStatus status = OK;


    list->root = NULL;
    list->size = 0;

    return status;
}


List* list_dtor(List* list)
{   
    CHECK_SOME_IS_NULL(NULL, list)


    Node* current_node = list->root; 
    for (size_t i = 0; i < list->size; i++)
    {
        if (current_node == NULL) break;
        Node* new_current_node = current_node->next;
        #ifndef TESTNUM
        free(current_node->value); 
        #endif
        free(current_node);
        current_node = new_current_node;
    }

    return NULL;
}


TestStatus list_push(List* list, Elem_t elem)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, list)
    TestStatus status = OK;

    list->root = create_new_node(elem, list->root, NULL, &status); 

    list->size++;


    return status;
}

TestStatus list_delete(List* list, Elem_t elem)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, list)
    TestStatus status = OK;


    Node* delete_node = list_find(*list, elem);
    status = cut_node(list, delete_node);

    return status;
}





Node* list_find(List list, Elem_t element)      /* return finded node pointer. If this value not in table -> return NULL */
{
    Node* current_node = list.root;

    while (current_node != NULL)
    {
        #ifdef TESTNUM
        if (current_node->value == element) return current_node;
        #else
        if (strcmp(current_node->value, element) == 0) return current_node;
        #endif

        current_node = current_node->next;
    }
    return NULL;
}



static struct Node* create_new_node(Elem_t elem, Node* next, Node* parent, TestStatus* status)
{
    CHECK_SOME_IS_NULL(NULL, status)
    if ((*status) != OK) return NULL;


    Node* new_node = (struct Node*) calloc(1, sizeof(Node));
    if (new_node == NULL)
    {
        *status = CALLOC_NODE_ERROR;
        return NULL;
    }

    new_node->value  = elem;
    new_node->next = next;
    new_node->parent = parent;

    return new_node;
}


static TestStatus cut_node(List* list, Node* delete_node)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, list)
    TestStatus status = OK;


    if (delete_node == NULL) return DELETE_STACK_WITHOUT_THIS_ELEMENT;


    if (delete_node->parent == NULL)
    {
        if (delete_node->parent == NULL) list->root = NULL;
        else
        {
            list->root = delete_node->next;
            delete_node->next->parent = NULL;
        }
    }
    else if (delete_node->parent == NULL)
    {
        delete_node->parent->next = NULL;
    }
    else
    {
        delete_node->parent->next = delete_node->next;
        delete_node->next->parent = delete_node->parent;
    }
    #ifndef TESTNUM
    free(delete_node->value); // ONLE FOR STRINGS!
    #endif
    free(delete_node);

    list->size--;

    return status;
}


// _______________ DUMP __________________

void list_print(const List* list)
{
    printf("LIST:\nsize - %lu\n", list->size);

    if (list->root != NULL) print_nodes(list->root);

    printf("\n\n");
}


static void print_nodes(const Node* node)
{
    #ifndef TESTNUM
    printf("%s ", node->value);
    #else
    printf("%d ", node->value);
    #endif

    if (node->next != NULL) print_nodes(node->next);
}

