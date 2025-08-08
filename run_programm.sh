# gcc -DTESTNUM main.c hash_table.c list.c strings_testing_hash_table.c numbers_testing_hash_table.c working_with_text.c -o hashtable
# gcc -g -O2 main.c Hash_Table/hash_table.c List/list.c Tests/strings_testing_hash_table.c Tests/numbers_testing_hash_table.c Processing_Text/working_with_text.c -o hashtable

# gcc -DDEBUG main.c Hash_Table/hash_table.c List/list.c Tests/strings_testing_hash_table.c Tests/numbers_testing_hash_table.c Processing_Text/working_with_text.c -o hashtable


# gcc -no-pie -g -O2 -DASM_STRCMP_OPTIM_ON main.c Hash_Table/hash_table.c List/list.c Tests/strings_testing_hash_table.c Tests/numbers_testing_hash_table.c Processing_Text/working_with_text.c ASM_optimization/ASM_strcmp.o -o hashtable

# gcc -msse4.2 -no-pie -g -O2 -DASM_STRCMP_OPTIM_ON -DCRC32_INTRINSIC main.c Hash_Table/hash_table.c List/list.c Tests/strings_testing_hash_table.c Tests/numbers_testing_hash_table.c Processing_Text/working_with_text.c ASM_optimization/ASM_strcmp.o -o hashtable

gcc -msse4.2 -no-pie -g -O2 -DASM_STRCMP_OPTIM_ON -DCRC32_INTRINSIC -D__ASM__INSERT_OPTIM_ON main.c Hash_Table/hash_table.c List/list.c Tests/strings_testing_hash_table.c Tests/numbers_testing_hash_table.c Processing_Text/working_with_text.c ASM_optimization/ASM_strcmp.o -o hashtable


