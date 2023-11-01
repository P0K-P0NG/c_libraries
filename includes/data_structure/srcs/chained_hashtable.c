/**
 * @file chained_hashtable.c
 * 
 * @brief 
 *  Structs and functions for chained hashtables.
 * 
 * @implements
 *  chained_hashtable.h
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-04
 */
#include <stdlib.h>
#include "key-value_linked_list.h"
#include "chained_hashtable.h"

CHAINED_HASH_T* chained_hash_create(unsigned long bucket_count)
{
    CHAINED_HASH_T* table = calloc(1, sizeof(CHAINED_HASH_T));
    if(table == NULL)
    {
        return NULL;
    }
    table->buckets = calloc(bucket_count, sizeof(KVP_LIST_T));
    if(table->buckets == NULL)
    {
        free(table);
        return NULL;
    }
    table->length = bucket_count;
    return table;
}

void chained_hash_clear(
    CHAINED_HASH_T *table, 
    void (*free_key)(void*), 
    void (*free_data)(void*))
{
    for(unsigned long i = 0; i < table->length; i++)
    {
        kvp_list_remove_all(&(table->buckets[i]), free_key, free_data);
    }
    free(table->buckets);
    free(table);
    table = NULL;
}

int chained_hash_add(
    CHAINED_HASH_T *table, 
    void *key, 
    void *data, 
    unsigned long (*hash_func)(const void*), 
    int (*comp_key)(const void*, const void*))
{
    unsigned long idx = hash_func(key)%table->length;
    if(comp_key == NULL)
    {
        return kvp_list_add_head(&table->buckets[idx], key, data);
    }
    return kvp_list_add(&table->buckets[idx], key, data, comp_key);
}

void* chained_hash_remove(
    CHAINED_HASH_T *table, 
    void *key, 
    unsigned long (*hash_func)(const void*), 
    int (*comp_key)(const void*, const void*), 
    void (*free_key)(void*))
{
    unsigned long idx = hash_func(key)%table->length;
    return kvp_list_remove(&table->buckets[idx], key, comp_key, free_key);
}

void* chained_hash_find(
    CHAINED_HASH_T *table, 
    const void *key, 
    unsigned long (*hash_func)(const void*), 
    int (*comp_key)(const void*, const void*))
{
    unsigned long idx = hash_func(key)%table->length;
    return kvp_list_find(&table->buckets[idx], key, comp_key);
}

int chained_hash_find_all(
    CHAINED_HASH_T *table, 
    const void *key, 
    void ***data_arr, 
    unsigned long (*hash_func)(const void*), 
    int (*comp_key)(const void*, const void*))
{
    unsigned long idx = hash_func(key)%table->length;
    return kvp_list_find_all(&table->buckets[idx], key, data_arr, comp_key);
}

int chained_hash_count_repeats(
    CHAINED_HASH_T *table, 
    const void *key, 
    unsigned long (*hash_func)(const void*), 
    int (*comp_key)(const void*, const void*))
{
    unsigned long idx = hash_func(key)%table->length;
    return kvp_list_count_repeats(&table->buckets[idx], key, comp_key);
}

void chained_hash_traverse(
    CHAINED_HASH_T *table, 
    void (*func)(void*, void*))
{
    for(unsigned long i = 0; i < table->length; i++)
    {
        kvp_list_traverse(&table->buckets[i], func);
    }
}

int chained_hash_chain_length(
    CHAINED_HASH_T *table, 
    const void *key, 
    unsigned long (*hash_func)(const void*))
{
    unsigned long idx = hash_func(key)%table->length;
    return table->buckets[idx].count;
}
