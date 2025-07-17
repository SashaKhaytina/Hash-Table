#include <stdio.h>

// #include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>

const char* RETURN_FILE_NAME = "processed_file.txt";

void processing_file(FILE* input_file, FILE* output_file);
size_t size_file(FILE* file);
size_t fill_new_text(char* old_text, char* new_text, size_t len_text);


int main(int argc, char* argv[])
{
    if (argc <= 1) 
    {
        printf("There are no arguments. Write file name please.\n");
        return 1; // error
    }

    char* file_name = argv[1];
    FILE* input_file  = fopen(file_name, "r");
    FILE* output_file = fopen(RETURN_FILE_NAME, "w");

    processing_file(input_file, output_file);
}


void processing_file(FILE* input_file, FILE* output_file)
{
    size_t len_text = size_file(input_file);
    char* text = (char*) calloc(len_text, sizeof(char));
    size_t size = fread(text, sizeof(char), len_text, input_file);
    if (size != len_text)
    {
        printf("ERROR read text\n");
        return; // error
    }

    char* new_text = (char*) calloc(len_text, sizeof(char));
    size_t len_new_text = fill_new_text(text, new_text, len_text);
    fwrite(new_text, sizeof(char), len_new_text, output_file);

    free(text);
    free(new_text);
}




size_t fill_new_text(char* old_text, char* new_text, size_t len_text)
{
    int counter_new_text = 0;
    for (size_t ind = 0; ind < len_text; ind++)
    {
        if (isalnum(old_text[ind]) != 0) new_text[counter_new_text++] = old_text[ind]; // letter or number
        else if (isspace(old_text[ind]) != 0)
        {
            new_text[counter_new_text++] = '\n';
            while (isspace(old_text[ind]) != 0) ind++; // skip spaces
            ind--;                                     // cycle for will do ++
        }
        else continue;
    }

    return counter_new_text;
}






size_t size_file(FILE* file)
{
    size_t size = 0;

    fseek(file, 0, SEEK_END);
    size = (size_t) ftell(file);
    fseek(file, 0, SEEK_SET);

    return size;
}

