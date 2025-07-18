# gcc -DTESTNUM main.c hash_table.c list.c strings_testing_hash_table.c numbers_testing_hash_table.c working_with_text.c -o hashtable
# gcc -g main.c Hash_Table/hash_table.c List/list.c Tests/strings_testing_hash_table.c Tests/numbers_testing_hash_table.c Processing_Text/working_with_text.c -o hashtable

# gcc -DDEBUG main.c hash_table.c list.c strings_testing_hash_table.c numbers_testing_hash_table.c working_with_text.c -o hashtable

# gcc -no-pie -Wall -g -DASM_STRCMP_OPTIM_ON main.c Hash_Table/hash_table.c List/list.c Tests/strings_testing_hash_table.c Tests/numbers_testing_hash_table.c Processing_Text/working_with_text.c ASM_optimization/ASM_strcmp.o -o hashtable


gcc -msse4.2 -no-pie -g -DASM_STRCMP_OPTIM_ON -DCRC32_INTRINSIC main.c Hash_Table/hash_table.c List/list.c Tests/strings_testing_hash_table.c Tests/numbers_testing_hash_table.c Processing_Text/working_with_text.c ASM_optimization/ASM_strcmp.o -o hashtable
