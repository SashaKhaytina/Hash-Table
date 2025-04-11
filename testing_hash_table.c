#include "testing_hash_table.h"

#include <stdlib.h>

const int    ELEMENTS_COUNT = 100;
const Elem_t MAX_ELEM       = 100;


TestStatus test_hash_table(Hash_Table* hash_table)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;


    status |= fill_hash_table(hash_table);
    CHECK_STATUS_OK(status)

    dump_hash_table(hash_table);

    status |= find_random_numbers_in_hash_table(hash_table);
    CHECK_STATUS_OK(status)

    return status;
}



TestStatus fill_hash_table(Hash_Table* hash_table)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;


    for (int i = 0; i < ELEMENTS_COUNT; i++)
    {
        CHECK_STATUS_OK(status)
        int element = rand() % (MAX_ELEM + 1);
        status = hash_table_insert(hash_table, element);
    }

    return status;
}



TestStatus find_random_numbers_in_hash_table(Hash_Table* hash_table)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;

    for (int i = 0; i < ELEMENTS_COUNT; i++)
    {
        int element = rand() % (MAX_ELEM + 1);
        if (hash_table_find(hash_table, element)) 
        {
            PRINTF_GREEN("There is element - "); printf("%d", element); PRINTF_GREEN(" in hash table\n");
        }
        else 
        {
            PRINTF_RED("There is no element - "); printf("%d", element); PRINTF_RED(" in hash table\n");
        }
    }

    return status;
}

