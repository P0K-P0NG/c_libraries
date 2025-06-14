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

struct ChainHashTable {       // Chained hashtable
    struct LListKVP *buckets; // array of linked list buckets
    unsigned long length;     // length of the bucket array
};

/**
 * @brief
 *  Creates a chained hashtable with a specific amount of buckets.
 *
 * @param bucket_count  Number of buckets
 *
 * @return New chained hashtable. NULL if unable to allocate memory.
 */
extern struct ChainHashTable *ChainHashTableCreate(unsigned long bucket_count);

/**
 * @brief
 *  Frees the entire chained hashtable and its data if given a function to free
 * it.
 *
 * @param table         chained hashtable to free
 * @param free_key      function to free the keys, NULL if not needed
 * @param free_data     function to free the data, NULL if not needed
 */
extern void ChainHashTableClear(struct ChainHashTable **table,
                                void (*free_key)(void *),
                                void (*free_data)(void *));

/**
 * @brief
 *  Adds a new key-value pair to a chained hash table, with the option to place
 * it in a specific position in the bucket using a data compare function.
 *
 * @note
 *  If provided the compare function must operate as follows: @n
 *  1) Returns int < 0 if key_1 should come before key_2 @n
 *  2) Returns int >= 0 if key_1 should come after key_2 @n
 *
 * @param table         chained hash table to add to
 * @param key           key of the new data
 * @param data          data to add
 * @param hash_func     key's hash function
 * @param comp_key      function to decide the new data's position
 *                      relative to pre-existing data, NULL if not needed
 *
 * @return
 *   1 : added successfully @n
 *   0 : unable to allocate memory @n
 */
extern int ChainHashTableAdd(struct ChainHashTable *table, void *key,
                             void *data,
                             unsigned long (*hash_func)(const void *),
                             int (*comp_key)(const void *, const void *));

/**
 * @brief
 *  Removes an key-value pair from a chained hash table
 *
 * @note
 *  The compare function must return 0 when keys match, and not 0 when it
 * doesn't.
 *
 * @param table         chained hash table to remove from
 * @param key           key of the data to remove
 * @param hash_func     key's hash function
 * @param comp_key      function to compare the keys with
 * @param free_key      function to free the keys, NULL if not needed
 *
 * @return Pointer to the removed data, NULL if not found.
 */
extern void *ChainHashTableRemove(struct ChainHashTable *table, void *key,
                                  unsigned long (*hash_func)(const void *),
                                  int (*comp_key)(const void *, const void *),
                                  void (*free_key)(void *));

/**
 * @brief
 *  Gets first instance data with a matching key in a specific bucket of a
 * chained hashtable.
 *
 * @note
 *  The compare function must return 0 when keys match, and not 0 when it
 * doesn't.
 *
 * @param table         chained hashtable to search
 * @param key           key of the data
 * @param hash_func     key's hash function
 * @param comp_key      function to compare the keys with
 *
 * @return Pointer to the data, NULL if not found.
 */
extern void *ChainHashTableFind(struct ChainHashTable *table, const void *key,
                                unsigned long (*hash_func)(const void *),
                                int (*comp_key)(const void *, const void *));

/**
 * @brief
 *  Gets all the data (in the form a dynamic pointer array) with a matching key
 * in a chained hashtable.
 *
 * @note
 *  The compare function must return 0 when keys match, and not 0 when it
 * doesn't.
 *
 * @param table         chained hashtable to search
 * @param key           key of the data
 * @param data_arr      dynamic pointer array to the data
 * @param hash_func     key's hash function
 * @param comp_key      function to compare the keys with
 *
 * @return
 *  Number of matching data found, -1 if memory allocation falied.
 */
extern int ChainHashTableFindAll(struct ChainHashTable *table, const void *key,
                                 void ***data_arr,
                                 unsigned long (*hash_func)(const void *),
                                 int (*comp_key)(const void *, const void *));

/**
 * @brief
 *  Counts the number of times a given key is matched in a chained hashtable.
 *
 * @note
 *  The compare function must return 0 when keys match, and not 0 when it
 * doesn't.
 *
 * @param table         chained hashtable to search
 * @param key           key of the data
 * @param hash_func     key's hash function
 * @param comp_key      function to compare the keys with
 *
 * @return The numebr of times the provided key is matched.
 */
extern int
ChainHashTableCountRepeats(struct ChainHashTable *table, const void *key,
                           unsigned long (*hash_func)(const void *),
                           int (*comp_key)(const void *, const void *));

/**
 * @brief
 *  Preforms a given function on all the keys and data (passed in this order) in
 * the chained hashtable
 *
 * @param table     chained hashtable to traverse
 * @param func      function to execute
 */
extern void ChainHashTableTraverse(struct ChainHashTable *table,
                                   void (*func)(void *, void *));

/**
 * @brief
 *  Gets the length of the bucket pointed to by the given key. Doesn't check
 * whether the key is in  the bucket or not.
 *
 * @param table         chained hastable to check
 * @param key           key to search for
 * @param hash_func     key's hash function
 *
 * @return Length of the bucket.
 */
extern int ChainHashTableChainLength(struct ChainHashTable *table,
                                     const void *key,
                                     unsigned long (*hash_func)(const void *));
#endif