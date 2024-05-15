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

ChainHashTable *ChainHashTableCreate(unsigned long bucket_count)
{
    ChainHashTable *table = calloc(1, sizeof(ChainHashTable));
    if (table == NULL)
    {
        return NULL;
    }
    table->buckets = calloc(bucket_count, sizeof(KVPList));
    if (table->buckets == NULL)
    {
        free(table);
        return NULL;
    }
    table->length = bucket_count;
    return table;
}

void ChainHashTableClear(
    ChainHashTable **table,
    void (*free_key)(void *),
    void (*free_data)(void *))
{
    for (unsigned long i = 0; i < (*table)->length; i++)
    {
        KVPListRemoveAll(&((*table)->buckets[i]), free_key, free_data);
    }
    free((*table)->buckets);
    free(*table);
    *table = NULL;
}

int ChainHashTableAdd(
    ChainHashTable *table,
    void *key,
    void *data,
    unsigned long (*hash_func)(const void *),
    int (*comp_key)(const void *, const void *))
{
    unsigned long idx = hash_func(key) % table->length;
    if (comp_key == NULL)
    {
        return KVPListAddHead(&table->buckets[idx], key, data);
    }
    return KVPListAdd(&table->buckets[idx], key, data, comp_key);
}

void *ChainHashTableRemove(
    ChainHashTable *table,
    void *key,
    unsigned long (*hash_func)(const void *),
    int (*comp_key)(const void *, const void *),
    void (*free_key)(void *))
{
    unsigned long idx = hash_func(key) % table->length;
    return KVPListRemove(&table->buckets[idx], key, comp_key, free_key);
}

void *ChainHashTableFind(
    ChainHashTable *table,
    const void *key,
    unsigned long (*hash_func)(const void *),
    int (*comp_key)(const void *, const void *))
{
    unsigned long idx = hash_func(key) % table->length;
    return KVPListFind(&table->buckets[idx], key, comp_key);
}

int ChainHashTableFindAll(
    ChainHashTable *table,
    const void *key,
    void ***data_arr,
    unsigned long (*hash_func)(const void *),
    int (*comp_key)(const void *, const void *))
{
    unsigned long idx = hash_func(key) % table->length;
    return KVPListFindAll(&table->buckets[idx], key, data_arr, comp_key);
}

int ChainHashTableCountRepeats(
    ChainHashTable *table,
    const void *key,
    unsigned long (*hash_func)(const void *),
    int (*comp_key)(const void *, const void *))
{
    unsigned long idx = hash_func(key) % table->length;
    return KVPListCountRepeats(&table->buckets[idx], key, comp_key);
}

void ChainHashTableTraverse(
    ChainHashTable *table,
    void (*func)(void *, void *))
{
    for (unsigned long i = 0; i < table->length; i++)
    {
        KVPListTraverse(&table->buckets[i], func);
    }
}

int ChainHashTableChainLength(
    ChainHashTable *table,
    const void *key,
    unsigned long (*hash_func)(const void *))
{
    unsigned long idx = hash_func(key) % table->length;
    return table->buckets[idx].count;
}
