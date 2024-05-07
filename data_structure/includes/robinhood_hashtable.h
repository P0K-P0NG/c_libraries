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

typedef struct hashtable_bucket_count   // made purely to make types feel more organized 
{
    unsigned long max;
    unsigned long used;
} HT_BUCKET_COUNT_T;

typedef struct robinhood_bucket // robinhood open address hashtable bucket
{
    void *key;          // Pointer to the key
    void *data;         // Pointer to the data
    unsigned long psl;  // probe sequence lengths, used to manage the hashtable
} RH_BUCKET_T;

typedef struct robinhood_open_hashtable // robinhood open address hastable
{
    RH_BUCKET_T **buckets;      // Dynamic array of pointers to the buckets
    HT_BUCKET_COUNT_T count;    // tracks the total amount of buckets and the amount used
    float max_load;             // limit proportion of load when rehashing should occur;
                                // 0 to disable the automatic rehashing
} RH_HASH_T;

/**
 * @brief 
 *  Creates a robinhood open address hashtable.
 * 
 * @param bucket_count      initial number of buckets
 * @param max_load_prop     load proportion to rehash at; 0-1;
 *                          0 if no rehash wanted
 * 
 * @return Pointer to the new hashtable, NULL if unable to allocate memory. 
 */
RH_HASH_T *robinhood_hash_create(unsigned long bucket_count, float max_load_prop);

/**
 * @brief 
 *  Deletes a robinhood open address hashtable. and frees it's contents 
 *  if provided with a function do so.
 * 
 * @param table         hashtable to delete
 * @param free_data     function to free data; NULL if not needed
 * @param free_key      function to free keys; NULL if not needed
 */
void robinhood_hash_clear(RH_HASH_T **table, void (*free_key)(void*), void (*free_data)(void*));

/**
 * @brief 
 *  Adds a new key-value pair to a robinhood open address hashtable. 
 *  Rehashes if the max load limit has been reached by doubling the current number of buckets.
 * 
 * @param table         hashtable to add to
 * @param key           key of the new item
 * @param data          data of the new item
 * @param hash_func     key's hash function
 * 
 * @return 
 *  1 : added successfully @n 
 *  0 : memory allocation falied @n 
 */
int robinhood_hash_add(RH_HASH_T *table, void *key, void *data, unsigned long (*hash_func)(const void*));

/**
 * @brief 
 *  Removes a key-value pair from a robinhood open address hashtable 
 *  and frees it's contents if provided with a function do so.
 * 
 * @note 
 *  The compare function must return 0 when keys match, and not 0 when it doesn't.
 * 
 * @param table         hashtable to remove from
 * @param key           key of the item to remove
 * @param hash_func     key's hash function
 * @param comp_key      function to compare the keys
 * @param free_data     function to free data; NULL if not needed
 * @param free_key      function to free keys; NULL if not needed
 * 
 * @return Pointer the data of the removed item, NULL if not found.
 */
void *robinhood_hash_remove(RH_HASH_T *table, void *key, unsigned long (*hash_func)(const void*), 
                            int (*comp_key)(const void*, const void*), void (*free_key)(void*));
                            
/**
 * @brief 
 *  Finds the data given the key in a robinhood open address hashtable.
 * 
 * @note 
 *  The compare function must return 0 when keys match, and not 0 when it doesn't.
 * 
 * @param table         hashtable to search
 * @param key           key of the data
 * @param hash_func     key's hash function
 * @param comp_key      function to compare the keys
 * 
 * @return Data corresponding to the key, NULL if not found.
 */
void *robinhood_hash_find(RH_HASH_T *table, void *key, unsigned long (*hash_func)(const void*), int (*comp_key)(const void*, const void*));

/**
 * @brief 
 *  Rehashes a robinhood open address hashtable.
 * 
 * @param table         hashtable to rehash
 * @param new_count     new number of buckets
 * @param hash_func     key's hash function
 * 
 * @return 
 *   1 : rehashed successfully @n
 *   0 : unable to allocate memory @n
 *  -1 : new count is less than current limit of available buckets (max_load_prop*max_count) @n
 */
int robinhood_rehash(RH_HASH_T *table, unsigned long new_count, unsigned long (*hash_func)(const void*));
#endif
