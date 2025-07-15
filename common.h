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



// -------------TIME---------------

#define START_TIMER struct timeval time_start = {}; gettimeofday(&time_start, NULL);

#define END_TIMER   struct timeval time_end   = {}; gettimeofday(&time_end,   NULL);\
                    average_time += ((double) (time_end.tv_sec * 1000 + time_end.tv_usec / 1000)) - ((double) time_start.tv_sec * 1000 + time_start.tv_usec / 1000);

#define COUNT_TIME(code) START_TIMER\
                        code\
                        END_TIMER





#ifdef TESTNUM
typedef int Elem_t;
#else
typedef char* Elem_t;
#endif

// #define TEST_MODE(code_for_str, code_for_num) #ifndef TESTNUM\
//                                               code_for_str\
//                                               #else\
//                                               code_for_num\
//                                               #endif



enum
{
    OK = 0,                                         /*!< Everything is correct. */
    DELETE_STACK_WITHOUT_THIS_ELEMENT = 1 << 1,     /*!< Delete elem, whose not in the Hash table. */
    CALLOC_NODE_ERROR = 1 << 2,                     /*!< Error memory allocation when create node for list. */
    ERROR_NULL_POINTER = 1 << 3,                    /*!< Pointer is NULL */
    ERROR_MDOE = 1 << 4                             /*!< Error mode test (called func for other mode). */

    // ERROR_CTOR = 1 << 1,                         /*!< Error memory allocation. */
    // ERROR_OPEN_FILE = 1 << 5,                    /*!< Error open file. */

    // ERROR = 1 << 6                                /*!< Default error */
} typedef TestStatus;


typedef struct Text Text;
struct Text 
{
    char** words;
    size_t count_words;
};



#endif
