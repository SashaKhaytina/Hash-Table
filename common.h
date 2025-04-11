#ifndef COMMON_H
#define COMMON_H


#define CHECK_STATUS_OK(status) if (status != OK) return status;


#define GLUING(a, b) a##b
#define DEFENITION(base_name, line) GLUING(base_name, line)
#define CHECK_SOME_IS_NULL(error, ... )\
                                        void* DEFENITION(args_array, __LINE__)[] = {__VA_ARGS__};\
                                        for (size_t i = 0; i < sizeof(DEFENITION(args_array, __LINE__))/ sizeof(DEFENITION(args_array, __LINE__)[0]); i++)\
                                        {\
                                            if (DEFENITION(args_array, __LINE__)[i] == NULL) return error;\
                                        }\


#define PRINTF_GREEN(string, ...)   printf("\x1b[32m" string "\x1b[0m", ##__VA_ARGS__)      /*!< Print green text. */
#define PRINTF_RED(string, ...)     printf("\x1b[31m" string "\x1b[0m", ##__VA_ARGS__)      /*!< Print red text. */



typedef int Elem_t;

// extern const int HASH_TABLE_SIZE = 50;


enum
{
    OK = 0,                                         /*!< Everything is correct. */
    DELETE_STACK_WITHOUT_THIS_ELEMENT = 1 << 1,     /*!< Delete elem, whose not in the Hash table. */
    CALLOC_NODE_ERROR = 1 << 2,                     /*!< Error memory allocation when create node for list. */
    ERROR_NULL_POINTER = 1 << 3,                    /*!< Pointer is NULL */

    // ERROR_CTOR = 1 << 1,                         /*!< Error memory allocation. */
    // ERROR_OPEN_FILE = 1 << 5,                    /*!< Error open file. */

    // ERROR = 1 << 6                                /*!< Default error */
} typedef TestStatus;



#endif
