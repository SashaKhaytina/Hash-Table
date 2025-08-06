#include "list.h"

#include <stdlib.h>
#include <string.h>


const size_t LEN_LIST = 61;
const int NO_ELEM_IN_LIST = -1;


static int  find_ind_in_array_by_ind_in_list(List* list, int ind);
static void print_nodes(const List* list, const Node* node);

#ifdef ASM_STRCMP_OPTIM_ON
int ASM_strcmp(const char* string1, const char* string2);
#endif




TestStatus list_ctor(List* list)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, list)
    TestStatus status = OK;


    list->array = (Node*) calloc(LEN_LIST, sizeof(Node));
    CHECK_SOME_IS_NULL(CALLOC_LIST_ERROR, list->array);
    
    list->array[0].value = POISON_ELEM_LIST; 
    list->array[0].next = 0;
    list->array[0].prev = 0;

    for (int i = 1; i < LEN_LIST; i++)
    {
        list->array[i].value = POISON_ELEM_LIST; 
        list->array[i].next = i + 1;
        list->array[i].prev = -1;
    } 

    list->array[LEN_LIST - 1].value = POISON_ELEM_LIST; 
    list->array[LEN_LIST - 1].next = 0;
    list->array[LEN_LIST - 1].prev = -1;

    list->size = 0;

    list->ind_first_free_node = 1;

    return status;
}

List* list_dtor(List* list)
{
    CHECK_SOME_IS_NULL(NULL, list)

    free(list->array);
    return NULL;
}


TestStatus list_push(List* list, Elem_t elem, int ind)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, list, elem)
    TestStatus status = OK;


    if (list->ind_first_free_node == 0)
    {
        printf("Список заполнен. Добавление невозможно\n");
        return ERROR_FULL_LIST;
    }

    if (ind > list->size + 1) // добавляет на индекс, который больше чем длина + 1
    {
        printf("Превышение максимального на данный момент индекса\n"); // переделать надпись
        return ERROR_IND_LIST;
    }

    int was_ind = find_ind_in_array_by_ind_in_list(list, ind);
    int empty_ind = list->ind_first_free_node;

    // Обновляем ind_first_free_node
    list->ind_first_free_node = list->array[list->ind_first_free_node].next;

    list->array[empty_ind].value = elem;
    list->array[list->array[was_ind].prev].next = empty_ind;
    list->array[empty_ind].next = was_ind;

    list->array[empty_ind].prev = list->array[was_ind].prev;
    list->array[was_ind].prev = empty_ind;

    list->size++;


    return status;
}



TestStatus list_delete(List* list, Elem_t elem)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, list)
    TestStatus status = OK;

    int ind = list_find(list, elem);
    if (ind == NO_ELEM_IN_LIST) return DELETE_STACK_WITHOUT_THIS_ELEMENT;

    return list_delete_by_ind(list, ind);
}



TestStatus list_delete_by_ind(List* list, int ind)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, list)
    TestStatus status = OK;


    if (list->size == 0)
    {
        printf("Попытка удаления из пустого списка\n");
        return DELETE_EMPTY_LIST;
    }
    if (0 >= ind || ind >= list->size)
    {
        printf("Incorrect index\n");
        return ERROR_IND_LIST;
    }

    int was_ind = find_ind_in_array_by_ind_in_list(list, ind);

    list->array[list->array[was_ind].next].prev = list->array[was_ind].prev;
    list->array[list->array[was_ind].prev].next = list->array[was_ind].next;
    list->size--;

    list->array[was_ind].value = POISON_ELEM_LIST;
    list->array[was_ind].prev = -1;
    // list->next[was_ind] = -1;

    // Обновляем ind_first_free_node
    list->array[was_ind].next = list->ind_first_free_node;
    list->ind_first_free_node = was_ind;

    return status;
}




int list_find(List* list, Elem_t element)
{
    #ifndef __ASM__INSERT_OPTIM_ON

    Node* list_array = list->array;
    int current_node = list_array[0].next; // TAIL

    #else

    Node* list_array = NULL;
    int current_node = 0;

    __asm__ __volatile__(
    "mov (%[list]), %%rax \n"                   // list->array = [list]
    "mov 8(%%rax), %%ebx \n"                    // list_array[0].next (because first elem in Node - Elem_t- 8 byte) (add $8, %%rax    mov (%%rax), %%ebx)

    : "=a" (list_array), "=b" (current_node)
    : [list] "r" (list)
    : "memory"                                  // Work with memory
    );
    #endif


    for (int step = 0; step < list->size; step++) 
    {
        #ifndef __ASM__INSERT_OPTIM_ON

        Node   current_node_in_list       = list_array[current_node];
        Elem_t value_current_node_in_list = current_node_in_list.value;

        #else
        Node*   current_node_in_list      = NULL;
        Elem_t value_current_node_in_list = NULL;

        size_t current_node_mem = current_node * sizeof(Node);

        __asm__ __volatile__(
        "mov %[list_array], %%rbx \n"
        "add %[current_node], %%rbx \n"                                     // rbx - pointer to list_array[current_node]
        "mov (%%rbx), %%rax \n"                                             // rax - current_node_in_list.value, because value - first elem in Node 

        : "=a" (value_current_node_in_list), "=b" (current_node_in_list)
        : [list_array] "r" (list_array), [current_node] "r" (current_node_mem)
        : "memory"                                                          // Work with memory
        );
        #endif


        #ifdef TESTNUM
        if (value_current_node_in_list == element) return current_node;
        #elif ASM_STRCMP_OPTIM_ON
        if (ASM_strcmp(value_current_node_in_list, element) == 0) return current_node;
        #else
        if (strcmp(value_current_node_in_list, element) == 0) return current_node;
        #endif


        #ifndef __ASM__INSERT_OPTIM_ON
        current_node = current_node_in_list.next;
        #else
        current_node = current_node_in_list->next;
        #endif
    }

    return NO_ELEM_IN_LIST;
}




// int list_find(List* list, Elem_t element)
// {
//     int current_node = list->array[0].next; // TAIL

//     for (int step = 0; step < list->size; step++) 
//     {
//         #ifdef TESTNUM
//         if (list->array[current_node].value == element) return current_node;
//         #elif ASM_STRCMP_OPTIM_ON
//         if (ASM_strcmp(list->array[current_node].value, element) == 0) return current_node;
//         #else
//         if (strcmp(list->array[current_node].value, element) == 0) return current_node;
//         #endif

//         current_node = list->array[current_node].next;
//     }

//     return NO_ELEM_IN_LIST;
// }



static int find_ind_in_array_by_ind_in_list(List* list, int ind)
{
    int current_node = list->array[0].next; // TAIL

    for (int step = 0; step < ind; step++) current_node = list->array[current_node].next;

    return current_node;
}



// _______________ DUMP __________________


void list_print(const List* list)
{
    printf("LIST:\nsize - %lu\n", list->size);

    if (list->size != 0) print_nodes(list, &(list->array[list->array[0].next]));

    printf("\n\n");
}


static void print_nodes(const List* list, const Node* node)
{
    #ifndef TESTNUM
    printf("%s ", node->value);
    #else
    printf("%d ", node->value);
    #endif

    if (node->next != 0) print_nodes(list, &(list->array[node->next]));
}


