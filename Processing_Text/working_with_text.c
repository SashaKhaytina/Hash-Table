#include "working_with_text.h"

#include <malloc.h>
#include <string.h>
#include <ctype.h>

const int MAX_WORD_SIZE = 30;

size_t size_file(FILE* file);


Text* get_elements(FILE* file)
{
    size_t len_text = size_file(file);
    char* text = (char*) calloc(len_text + 1, sizeof(char));
    size_t size = fread(text, sizeof(char), len_text, file);
    if (size != len_text)
    {
        printf("ERROR read processed text\n");
        return NULL; // error
    }

    Text* struct_with_words = (Text*) calloc(1, sizeof(Text));

    struct_with_words->words = (char**) calloc(len_text, sizeof(char*));
    struct_with_words->count_words = 0;
    

    char elem[MAX_WORD_SIZE]; 
    char* current_text = text;
    while(sscanf(current_text, "%s", elem) == 1) 
    {
        char* added_elem = calloc(MAX_WORD_SIZE, sizeof(char));
        strcpy(added_elem, elem);
        struct_with_words->words[struct_with_words->count_words++] = added_elem;

        current_text += strlen(added_elem);
        
        
        while (*current_text != '\0' && isspace(*current_text)) current_text++; // skip spaces
    }

    struct_with_words->words = realloc(struct_with_words->words, struct_with_words->count_words * sizeof(char*)); // for save size array

    free(text);

    return struct_with_words;
}



Text* free_struct_text(Text* words)
{
    for (int i = 0; i < words->count_words; i++)
    {
        free(words->words[i]);
    }
    free(words->words);
    free(words);

    return NULL;
}



size_t size_file(FILE* file)
{
    size_t size = 0;

    fseek(file, 0, SEEK_END);
    size = (size_t) ftell(file);
    fseek(file, 0, SEEK_SET);

    return size;
}
