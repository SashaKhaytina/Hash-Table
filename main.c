#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <time.h>

#include "hash_table.h"

#include "working_with_text.h"
#include "numbers_testing_hash_table.h"
#include "strings_testing_hash_table.h"

const int HASH_TABLE_SIZE = 250;
const char* PROCESSED_FILE_NAME = "processed_file.txt";



int main()
{
    srand(time(NULL));
    double average_time = 0;


    Hash_Table* hash_table = hash_table_ctor(HASH_TABLE_SIZE);

    #ifdef TESTNUM
    num_test_hash_table(hash_table);
    #else
    FILE* file = fopen(PROCESSED_FILE_NAME, "r");
    Text* words = get_elements(file);
    fclose(file);

    // for (int i = 0; i < words->count_words; i++)
    // {
    //     printf("%s - str\n", words->words[i]);
    // }

    COUNT_TIME(str_test_hash_table(hash_table, words);)

    free(words->words);
    free(words);
    #endif

    hash_table_dtor(hash_table);

    PRINTF_GREEN("TEST Time: "); printf("%f, мс; %f, c\n", average_time, average_time / 1000);
}