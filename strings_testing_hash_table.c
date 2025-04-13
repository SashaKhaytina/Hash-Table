#include "strings_testing_hash_table.h"

#include <stdlib.h>

const int SIZE_RANDOM_WORD = 10;
const size_t COUNT_TESTS_CYCLE = 700;


TestStatus str_test_hash_table(Hash_Table* hash_table, Text* words)
{
    #ifndef TESTNUM
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;


    status |= str_fill_hash_table(hash_table, words);
    CHECK_STATUS_OK(status)


    #ifdef DEBUG
    dump_hash_table(hash_table);
    #endif

    for (size_t i = 0; i < COUNT_TESTS_CYCLE; i++)
    {
        status |= find_words_in_hash_table(hash_table, words);
        CHECK_STATUS_OK(status)

        status |= find_random_words_in_hash_table(hash_table);
        CHECK_STATUS_OK(status)
    }

    return status;

    #else
    return ERROR_MDOE;
    #endif
}



TestStatus str_fill_hash_table(Hash_Table* hash_table, Text* words)
{
    #ifndef TESTNUM
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;


    for (int i = 0; i < words->count_words; i++)
    {
        CHECK_STATUS_OK(status)
        status = hash_table_insert(hash_table, words->words[i]);
    }

    return status;

    #else
    return ERROR_MDOE;
    #endif
}



TestStatus find_words_in_hash_table(Hash_Table* hash_table, Text* words)
{
    #ifndef TESTNUM
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;


    for (int i = 0; i < words->count_words; i++)
    {
        Elem_t element = words->words[i];
        if (hash_table_find(hash_table, element)) 
        {
            #ifdef DEBUG
            PRINTF_GREEN("There is element - "); printf("%s", element); PRINTF_GREEN(" in hash table\n");
            #endif
        }
        else 
        {
            #ifdef DEBUG
            PRINTF_RED("There is no element - "); printf("%s", element); PRINTF_RED(" in hash table\n");
            #endif
        }
    }

    return status;

    #else
    return ERROR_MDOE;
    #endif
}


TestStatus find_random_words_in_hash_table(Hash_Table* hash_table)
{
    #ifndef TESTNUM
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;

    char* first_word = "tukhis";
    if (hash_table_find(hash_table, "tukhis")) 
    {
        #ifdef DEBUG
        PRINTF_GREEN("There is element - "); printf("%s", first_word); PRINTF_GREEN(" in hash table\n");
        #endif
    }
    else 
    {
        #ifdef DEBUG
        PRINTF_RED("There is no element - "); printf("%s", first_word); PRINTF_RED(" in hash table\n");
        #endif
    }


    for (int i = 0; i < COUNT_TESTS_CYCLE; i++)
    {
        char element[SIZE_RANDOM_WORD + 1] = {};
        for (int j = 0; j < SIZE_RANDOM_WORD; j++)
        {
            int letter = 97 + rand() % 26;
            element[j] = letter;
        }

        if (hash_table_find(hash_table, element)) 
        {
            #ifdef DEBUG
            PRINTF_GREEN("There is element - "); printf("%s", element); PRINTF_GREEN(" in hash table\n");
            #endif
        }
        else 
        {
            #ifdef DEBUG
            PRINTF_RED("There is no element - "); printf("%s", element); PRINTF_RED(" in hash table\n");
            #endif
        }
    }

    return status;

    #else
    return ERROR_MDOE;
    #endif
}
