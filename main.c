#include <stdio.h>

#include "hash_table.h"
#include "testing_hash_table.h"

const int HASH_TABLE_SIZE = 50;


int main()
{
    printf("Something\n");

    Hash_Table* hash_table = hash_table_ctor(HASH_TABLE_SIZE);


    test_hash_table(hash_table);

    hash_table_dtor(hash_table);
}