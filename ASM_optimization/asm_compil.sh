# nasm -g -f elf64 -l ASM_strcmp.lst ASM_strcmp.s  
# ld -o ASM_strcmp ASM_strcmp.o
# ./ASM_strcmp

nasm -g -f elf64 -l func_MyPrintf.lst func_MyPrintf.s -o func_MyPrintf.o
