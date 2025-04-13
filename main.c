#include <stdio.h>

#include "hash_table.h"

#include "working_with_text.h"
#include "numbers_testing_hash_table.h"
#include "strings_testing_hash_table.h"

const int HASH_TABLE_SIZE = 250;
const char* PROCESSED_FILE_NAME = "processed_file.txt";



int main()
{
    FILE* file = fopen(PROCESSED_FILE_NAME, "r");
    Text* words = get_elements(file);


    // for (int i = 0; i < words->count_words; i++)
    // {
    //     printf("%s - str\n", words->words[i]);
    // }


    Hash_Table* hash_table = hash_table_ctor(HASH_TABLE_SIZE);

    #ifdef TESTNUM
    num_test_hash_table(hash_table);
    #else
    str_test_hash_table(hash_table, words);
    #endif


    hash_table_dtor(hash_table);
}