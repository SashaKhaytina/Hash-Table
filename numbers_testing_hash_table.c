#include "numbers_testing_hash_table.h"

#include <stdlib.h>

#ifdef TESTNUM
const int    ELEMENTS_COUNT = 1000;
const Elem_t MAX_ELEM       = 400;
#endif

TestStatus num_test_hash_table(Hash_Table* hash_table)
{
    #ifdef TESTNUM
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;


    status |= num_fill_hash_table(hash_table);
    CHECK_STATUS_OK(status)

    dump_hash_table(hash_table);

    status |= find_random_numbers_in_hash_table(hash_table);
    CHECK_STATUS_OK(status)

    return status;

    #else
    return ERROR_MDOE; // вообще код можно и сюда вставить, но слишком большая функция будет.
                       // или можно просто отдельно функцию распределитель сделать.
    #endif
}



TestStatus num_fill_hash_table(Hash_Table* hash_table)
{
    #ifdef TESTNUM
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;


    for (int i = 0; i < ELEMENTS_COUNT; i++)
    {
        CHECK_STATUS_OK(status)
        int element = rand() % (MAX_ELEM + 1);
        status = hash_table_insert(hash_table, element);
    }

    return status;

    #else
    return ERROR_MDOE;
    #endif
}



TestStatus find_random_numbers_in_hash_table(Hash_Table* hash_table)
{
    #ifdef TESTNUM
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
    
    #else
    return ERROR_MDOE;
    #endif
}

