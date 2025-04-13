#ifndef STRINGS_TESTING_HASH_TABLE_H
#define STRINGS_TESTING_HASH_TABLE_H

#include "hash_table.h"

/*!
 * \brief Print execution statistic to cmd
 *
 * DISCLAIMER: NEVER use this function (at home)
 *  
 * \param[out] hash_table - Hash Table
 * \return return execution status (error code)
 */
TestStatus str_test_hash_table(Hash_Table* hash_table, Text* words);


/*!
 * \brief Fill Hash Table words from words array
 * 
 * \param[out] hash_table - Hash Table
 * \return return execution status (error code)
 */
TestStatus str_fill_hash_table(Hash_Table* hash_table, Text* words);


/*!
 * \brief Find words from words array in Hash Table
 * 
 * \param[out] hash_table - Hash Table
 * \return return execution status (error code)
 */
TestStatus find_words_in_hash_table(Hash_Table* hash_table, Text* words);


/*!
 * \brief Find random words from words array in Hash Table
 * 
 * \param[out] hash_table - Hash Table
 * \return return execution status (error code)
 */
TestStatus find_random_words_in_hash_table(Hash_Table* hash_table);




#endif