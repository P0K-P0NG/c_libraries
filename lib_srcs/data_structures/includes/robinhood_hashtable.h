/**
 * @file robinhood_hashtable.h
 *
 * @brief
 *  Structs and functions for robinhood open address hashtables.
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-22
 */
#ifndef ROBINHOOD_HASHTABLE_H
#define ROBINHOOD_HASHTABLE_H

#include <stddef.h>

struct RobinHTBucket { // robinhood open address hashtable bucket
    void *key;         // Pointer to the key
    void *data;        // Pointer to the data
    size_t psl;        // probe sequence lengths, used to manage the hashtable
};

struct RobinHashTable {             // robinhood open address hastable
    struct RobinHTBucket **buckets; // Dynamic array of pointers to the buckets
    struct {
        size_t max;
        size_t used;
    } count;        // tracks the total amount of buckets and the amount used
    float max_load; // limit proportion of load when rehashing should occur;
                    // 0 to disable the automatic rehashing
    size_t (*hash)(const void *);
    /**
     *  The compare function must operate as follows: @n
     *  1) Returns int < 0 if key_1 should come before key_2 @n
     *  2) Returns int >= 0 if key_1 should come after key_2 @n
     */
    int (*comp_key)(const void *, const void *);
};

/**
 * @brief
 *  Creates a robinhood open address hashtable.
 *
 * @note
 *  The compare function must operate as follows: @n
 *  1) Returns int < 0 if key_1 should come before key_2 @n
 *  2) Returns int >= 0 if key_1 should come after key_2 @n
 *
 * @param[in] bucket_count      initial number of buckets
 * @param[in] max_load_prop     load proportion to rehash at; 0-1;
 *                          0 if no rehash wanted
 * @param[in] hash_func         function to hash keys
 * @param[in] comp_key          function to compare the keys
 *
 * @return Pointer to the new hashtable, NULL if unable to allocate memory.
 */
extern struct RobinHashTable *
RobinHashTableCreate(size_t bucket_count, float max_load_prop,
                     size_t (*hash_func)(const void *),
                     int (*comp_key)(const void *, const void *));

/**
 * @brief
 *  Deletes a robinhood open address hashtable. and frees it's contents
 *  if provided with a function do so.
 *
 * @param[in,out] p_table       hashtable to delete
 * @param free_data     function to free data; NULL if not needed
 * @param free_key      function to free keys; NULL if not needed
 */
extern void RobinHashTableClear(struct RobinHashTable **p_table,
                                void (*free_data)(void *),
                                void (*free_key)(void *));

/**
 * @brief
 *  Adds a new key-value pair to a robinhood open address hashtable.
 *  Rehashes if the max load limit has been reached by doubling the current
 *  number of buckets.
 *
 * @param[in,out] table         hashtable to add to
 * @param[in]     key           key of the new item
 * @param[in]     data          data of the new item
 *
 * @return
 *  1 : added successfully @n
 *  0 : memory allocation falied @n
 */
extern int RobinHashTableAdd(struct RobinHashTable *table, void *key,
                             void *data);

/**
 * @brief
 *  Removes a key-value pair from a robinhood open address hashtable
 *  and frees it's contents if provided with a function do so.
 *
 * @param[in,out] table         hashtable to remove from
 * @param[in]     key           key of the item to remove=
 * @param[in]     free_data     function to free data; NULL if not needed
 * @param[in]     free_key      function to free keys; NULL if not needed
 *
 * @return Pointer the data of the removed item, NULL if not found.
 */
extern void *RobinHashTableRemove(struct RobinHashTable *table, void *key,
                                  void (*free_data)(void *),
                                  void (*free_key)(void *));

/**
 * @brief
 *  Finds the data given the key in a robinhood open address hashtable.
 *
 * @param[in] table         hashtable to search
 * @param[in] key           key of the data
 *
 * @return Data corresponding to the key, NULL if not found.
 */
extern void *RobinHashTableFind(struct RobinHashTable *table, void *key);

/**
 * @brief
 *  Rehashes a robinhood open address hashtable.
 *
 * @param[in,out] table         hashtable to rehash
 * @param[in]     new_count     new number of buckets
 *
 * @return
 *   1 : rehashed successfully @n
 *   0 : unable to allocate memory @n
 *  -1 : new count is less than current limit of available buckets
 *       (max_load_prop*max_count) @n
 */
extern int RobinHashTableRehash(struct RobinHashTable *table, size_t new_count);
#endif
