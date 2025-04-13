#ifndef TESTING_HASH_TABLE_H
#define TESTING_HASH_TABLE_H

#include "hash_table.h"


// extern const int    ELEMENTS_COUNT = 100;
// extern const Elem_t MAX_ELEM       = 100;


/*!
 * \brief Print execution statistic to cmd
 *
 * DISCLAIMER: NEVER use this function (at home)
 *  
 * \param[out] hash_table - Hash Table
 * \return return execution status (error code)
 */
TestStatus num_test_hash_table(Hash_Table* hash_table);


/*!
 * \brief Fill Hash Table random nums from [0;100]
 * 
 * \param[out] hash_table - Hash Table
 * \return return execution status (error code)
 */
TestStatus num_fill_hash_table(Hash_Table* hash_table);


/*!
 * \brief Find random nums from [0;100] in Hash Table
 * 
 * \param[out] hash_table - Hash Table
 * \return return execution status (error code)
 */
TestStatus find_random_numbers_in_hash_table(Hash_Table* hash_table);


#endif