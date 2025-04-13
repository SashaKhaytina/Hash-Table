#include "hash_table.h"

#include <malloc.h>




Hash_Table* hash_table_ctor(size_t size)
{
    Hash_Table* hash_table = (Hash_Table*) calloc(1, sizeof(Hash_Table));
    CHECK_SOME_IS_NULL(NULL, hash_table)

    hash_table->table = (List*) calloc(size, sizeof(List));
    if (hash_table->table == NULL)
    {
        free(hash_table);
        return NULL;
    }

    hash_table->size = size;

    for (size_t i = 0; i < hash_table->size; i++)
    {
        List* current_list = &(hash_table->table[i]);
        list_ctor(current_list);                        // тут не нули будут..? Sasha pohody shizy slovila
    }

    return hash_table;
}


Hash_Table* hash_table_dtor(Hash_Table* hash_table)
{
    CHECK_SOME_IS_NULL(NULL, hash_table)

    for (size_t i = 0; i < hash_table->size; i++)
    {
        list_dtor(&(hash_table->table[i]));

        // No lose mem here?

        /*
        
        [   | list |   |   | ] - table
              |
               ->[node] -> [node] -> [] -> ...
        
        */

    }
    
    free(hash_table->table); 
    free(hash_table);
    return NULL;
}





TestStatus hash_table_insert(Hash_Table* hash_table, Elem_t element)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;

    
    #ifdef TESTNUM
    size_t ind = hash_function(element) % hash_table->size;
    #else
    size_t ind = FNV1aHash(element) % hash_table->size;
    #endif

    if (list_find(hash_table->table[ind], element)) return OK; // no same elements
    status = list_push(&(hash_table->table[ind]), element);

    return status;
}


TestStatus hash_table_delete(Hash_Table* hash_table, Elem_t element)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;

    
    #ifdef TESTNUM
    size_t ind = hash_function(element) % hash_table->size;
    #else
    size_t ind = FNV1aHash(element) % hash_table->size;
    #endif

    status = list_delete(&(hash_table->table[ind]), element);

    return status;
}

bool hash_table_find(Hash_Table* hash_table, Elem_t element)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;

    #ifdef TESTNUM
    size_t ind = hash_function(element) % hash_table->size;
    #else
    size_t ind = FNV1aHash(element) % hash_table->size;
    #endif

    if (list_find(hash_table->table[ind], element) == NULL) return false;
    return true;
}


size_t hash_function(Elem_t element) // ее использовать по модулю длины хеш-таблицы
{
    return (size_t) element;    // ┐(￣ヘ￣)┌  <(Good hash-function)
}


size_t FNV1aHash(char* buf)
{
    
    size_t FNV_32_PRIME = 0x01000193;
    size_t hval = 0x811c9dc5;

    while (*buf)
    {
        hval ^= (size_t) *buf; // xor with ASCII code letter
        buf++;
        hval *= FNV_32_PRIME;
    }

    return hval;
}


// _______________ DUMP __________________

void dump_hash_table(Hash_Table* hash_table)
{
    CHECK_SOME_IS_NULL(, hash_table)

    for (size_t i = 0; i < hash_table->size; i++)
    {
        PRINTF_GREEN("HASH FUNC IS (mod hash table size): ");
        printf("%ld", i);

        list_print(&(hash_table->table[i]));
    }
}