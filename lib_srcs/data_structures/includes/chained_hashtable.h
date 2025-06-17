/**
 * @file chained_hashtable.h
 *
 * @brief
 *  Structs and functions for chained hashtables.
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-04
 */
#ifndef CHAINED_HASHTABLE_H
#define CHAINED_HASHTABLE_H

#include "linked_list_kvp.h"
#include <stddef.h>

struct ChainHashTable {
    struct LListKVP *buckets; // array of linked list buckets
    size_t length;            // length of the bucket array
    size_t (*hash)(const void *);
};

/**
 * @brief
 *  Creates a chained hashtable with a specific amount of buckets.
 *
 * @note
 *  If provided the compare function must operate as follows: @n
 *  1) Returns int < 0 if key_1 should come before key_2 @n
 *  2) Returns int >= 0 if key_1 should come after key_2 @n
 *
 * @param[in] bucket_count  number of buckets
 * @param[in] hash_func     function to hash keys
 * @param[in] comp_key      function to compare the keys
 *
 * @return New chained hashtable. NULL if unable to allocate memory.
 */
extern struct ChainHashTable *
ChainHashTableCreate(size_t bucket_count, size_t (*hash_func)(const void *),
                     int (*comp_key)(const void *, const void *));

/**
 * @brief
 *  Frees the entire chained hashtable and its data if given a function to free
 *  it.
 *
 * @param[in,out] p_table       chained hashtable to free
 * @param[in]     free_key      function to free the keys, NULL if not needed
 * @param[in]     free_data     function to free the data, NULL if not needed
 */
extern void ChainHashTableClear(struct ChainHashTable **p_table,
                                void (*free_key)(void *),
                                void (*free_data)(void *));

/**
 * @brief
 *  Adds a new key-value pair to a chained hash table, with the option to place
 *  it in a specific position in the bucket using a data compare function.
 *
 * @param[in,out] table     chained hash table to add to
 * @param[in]     key       key of the new data
 * @param[in]     data      data to add
 *
 * @return
 *   1 : added successfully @n
 *   0 : unable to allocate memory @n
 */
extern int ChainHashTableAdd(struct ChainHashTable *table, void *key,
                             void *data);

/**
 * @brief
 *  Removes an key-value pair from a chained hash table
 *
 * @param[in,out] table     chained hash table to remove from
 * @param[in]     key       key of the data to remove
 * @param[in]     free_key  function to free the keys, NULL if not needed
 *
 * @return Pointer to the removed data, NULL if not found.
 */
extern void *ChainHashTableRemove(struct ChainHashTable *table, void *key,
                                  void (*free_key)(void *));

/**
 * @brief
 *  Gets first instance data with a matching key in a specific bucket of a
 *  chained hashtable.
 *
 * @param[in] table     chained hashtable to search
 * @param[in] key       key of the data
 *
 * @return Pointer to the data, NULL if not found.
 */
extern void *ChainHashTableFind(struct ChainHashTable *table, const void *key);

/**
 * @brief
 *  Gets all the data (in the form a dynamic pointer array) with a matching key
 *  in a chained hashtable.
 *
 * @param[in]  table        chained hashtable to search
 * @param[in]  key          key of the data
 * @param[out] ptr_arr      dynamic pointer array to the data
 * @param[out] count        variable to store the number of matches
 *
 * @return
 *  true  : execution successful @n
 *  false : memory allocation failed @n
 */
extern bool ChainHashTableFindAll(struct ChainHashTable *table, const void *key,
                                  void ***ptr_arr, size_t *count);

/**
 * @brief
 *  Counts the number of times a given key is matched in a chained hashtable.
 *
 * @param[in] table     chained hashtable to search
 * @param[in] key       key of the data
 *
 * @return The numebr of times the provided key is matched.
 */
extern int ChainHashTableCountRepeats(struct ChainHashTable *table,
                                      const void *key);

/**
 * @brief
 *  Preforms a given function on all the keys and data (passed in this order) in
 *  the chained hashtable
 *
 * @param[in,out] table     chained hashtable to traverse
 * @param[in]     func      function to execute
 */
extern void ChainHashTableTraverse(struct ChainHashTable *table,
                                   void (*func)(void *, void *));

/**
 * @brief
 *  Gets the length of the bucket pointed to by the given key. Doesn't check
 *  whether the key is in  the bucket or not.
 *
 * @param[in] table     chained hastable to check
 * @param[in] key       key to search for
 *
 * @return Length of the bucket.
 */
extern int ChainHashTableChainLength(struct ChainHashTable *table,
                                     const void *key);
#endif