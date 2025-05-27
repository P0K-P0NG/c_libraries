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
#include "chained_hashtable.h"
#include "linked_list_kvp.h"
#include <stdlib.h>

struct ChainHashTable *ChainHashTableCreate(unsigned long bucket_count)
{
    struct ChainHashTable *table = calloc(1, sizeof(struct ChainHashTable));
    if (table == NULL) {
        return NULL;
    }
    table->buckets = calloc(bucket_count, sizeof(struct LListKVP));
    if (table->buckets == NULL) {
        free(table);
        return NULL;
    }
    table->length = bucket_count;
    return table;
}

void ChainHashTableClear(struct ChainHashTable **table,
                         void (*free_key)(void *), void (*free_data)(void *))
{
    for (unsigned long i = 0; i < (*table)->length; i++) {
        LListKVPRemoveAll(&((*table)->buckets[i]), free_key, free_data);
    }
    free((*table)->buckets);
    free(*table);
    *table = NULL;
}

int ChainHashTableAdd(struct ChainHashTable *table, void *key, void *data,
                      unsigned long (*hash_func)(const void *),
                      int (*comp_key)(const void *, const void *))
{
    unsigned long idx = hash_func(key) % table->length;
    if (comp_key == NULL) {
        return LListKVPAddHead(&table->buckets[idx], key, data);
    }
    return LListKVPAdd(&table->buckets[idx], key, data, comp_key);
}

void *ChainHashTableRemove(struct ChainHashTable *table, void *key,
                           unsigned long (*hash_func)(const void *),
                           int (*comp_key)(const void *, const void *),
                           void (*free_key)(void *))
{
    unsigned long idx = hash_func(key) % table->length;
    return LListKVPRemove(&table->buckets[idx], key, comp_key, free_key);
}

void *ChainHashTableFind(struct ChainHashTable *table, const void *key,
                         unsigned long (*hash_func)(const void *),
                         int (*comp_key)(const void *, const void *))
{
    unsigned long idx = hash_func(key) % table->length;
    return LListKVPFind(&table->buckets[idx], key, comp_key);
}

int ChainHashTableFindAll(struct ChainHashTable *table, const void *key,
                          void ***data_arr,
                          unsigned long (*hash_func)(const void *),
                          int (*comp_key)(const void *, const void *))
{
    unsigned long idx = hash_func(key) % table->length;
    return LListKVPFindAll(&table->buckets[idx], key, data_arr, comp_key);
}

int ChainHashTableCountRepeats(struct ChainHashTable *table, const void *key,
                               unsigned long (*hash_func)(const void *),
                               int (*comp_key)(const void *, const void *))
{
    unsigned long idx = hash_func(key) % table->length;
    return LListKVPCountRepeats(&table->buckets[idx], key, comp_key);
}

void ChainHashTableTraverse(struct ChainHashTable *table,
                            void (*func)(void *, void *))
{
    for (unsigned long i = 0; i < table->length; i++) {
        LListKVPTraverse(&table->buckets[i], func);
    }
}

int ChainHashTableChainLength(struct ChainHashTable *table, const void *key,
                              unsigned long (*hash_func)(const void *))
{
    unsigned long idx = hash_func(key) % table->length;
    return table->buckets[idx].count;
}
