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
#include <assert.h>
#include <stdlib.h>

struct ChainHashTable *
ChainHashTableCreate(size_t bucket_count, size_t (*hash_func)(const void *),
                     int (*comp_key)(const void *, const void *))
{
    assert(hash_func != NULL);

    struct ChainHashTable *table = calloc(1, sizeof(struct ChainHashTable));
    if (table == NULL) {
        return NULL;
    }
    table->buckets = LListKVPCreate(comp_key);
    if (table->buckets == NULL) {
        free(table);
        return NULL;
    }
    table->length = bucket_count;
    table->hash = hash_func;
    return table;
}

void ChainHashTableClear(struct ChainHashTable **p_table,
                         void (*free_key)(void *), void (*free_data)(void *))
{
    assert(p_table != NULL);
    assert(*p_table != NULL);

    for (size_t i = 0; i < (*p_table)->length; i++) {
        LListKVPRemoveAll(&((*p_table)->buckets[i]), free_key, free_data);
    }
    free((*p_table)->buckets);
    free(*p_table);
    *p_table = NULL;
}

int ChainHashTableAdd(struct ChainHashTable *table, void *key, void *data)
{
    assert(table != NULL);

    size_t idx = table->hash(key) % table->length;
    return LListKVPAdd(&table->buckets[idx], key, data);
}

void *ChainHashTableRemove(struct ChainHashTable *table, void *key,
                           void (*free_key)(void *))
{
    assert(table != NULL);

    size_t idx = table->hash(key) % table->length;
    return LListKVPRemove(&table->buckets[idx], key, free_key);
}

void *ChainHashTableFind(struct ChainHashTable *table, const void *key)
{
    assert(table != NULL);

    size_t idx = table->hash(key) % table->length;
    return LListKVPFind(&table->buckets[idx], key);
}

bool ChainHashTableFindAll(struct ChainHashTable *table, const void *key,
                           void ***ptr_arr, size_t *count)
{
    assert(table != NULL);

    size_t idx = table->hash(key) % table->length;
    return LListKVPFindAll(&table->buckets[idx], key, ptr_arr, count);
}

int ChainHashTableCountRepeats(struct ChainHashTable *table, const void *key)
{
    assert(table != NULL);

    size_t idx = table->hash(key) % table->length;
    return LListKVPCountRepeats(&table->buckets[idx], key);
}

void ChainHashTableTraverse(struct ChainHashTable *table,
                            void (*func)(void *, void *))
{
    assert(table != NULL);
    assert(func != NULL);

    for (size_t i = 0; i < table->length; i++) {
        LListKVPTraverse(&table->buckets[i], func);
    }
}

int ChainHashTableChainLength(struct ChainHashTable *table, const void *key)
{
    assert(table != NULL);

    size_t idx = table->hash(key) % table->length;
    return table->buckets[idx].count;
}
