#ifndef HASH_TABLE_H
#define HASH_TABLE_H


#include <stdio.h>
#include <stdbool.h>

#include "list.h"


typedef struct Hash_Table Hash_Table;
struct Hash_Table
{
    List* table;        /* Array with linked lists (there are elem-s with same h(elem) in list) */
    size_t size;        /* Size of Hash_Table (len(array)) */
};


Hash_Table* hash_table_ctor(size_t size);
Hash_Table* hash_table_dtor(Hash_Table* hash_table);

TestStatus hash_table_insert(Hash_Table* hash_table, Elem_t element);
TestStatus hash_table_delete(Hash_Table* hash_table, Elem_t element);
bool       hash_table_find  (Hash_Table* hash_table, Elem_t element);

void dump_hash_table(Hash_Table* hash_table);

size_t hash_function(Elem_t element);   /* return ind in hash table */
size_t FNV1aHash(char* buf);
size_t hash_function_polin(Elem_t element);



#endif
