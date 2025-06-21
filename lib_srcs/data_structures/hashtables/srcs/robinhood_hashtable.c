/**
 * @file robinhood_hashtable.c
 *
 * @brief
 *  Structs and functions for robinhood open address hashtables.
 *
 * @implements
 *  robinhood_hashtable.h
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-22
 */
#include "robinhood_hashtable.h"
#include "swap_funcs.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void _addBucket(struct RobinHTBucket **buckets,
                       RobinHTBucket_t *new_bucket, size_t i,
                       size_t max_count);

RobinHashTable_t *
RobinHashTableCreate(size_t bucket_count, float max_load_prop,
                     size_t (*hash_func)(const void *),
                     int (*comp_key)(const void *, const void *))
{
    assert(hash_func != NULL);
    assert(comp_key != NULL);

    RobinHashTable_t *new_table = calloc(1, sizeof(RobinHashTable_t));
    if (new_table == NULL) {
        return NULL;
    }
    new_table->count.max = bucket_count;
    new_table->max_load = max_load_prop;
    new_table->hash = hash_func;
    new_table->comp_key = comp_key;
    new_table->buckets = calloc(bucket_count, sizeof(RobinHTBucket_t *));
    if (new_table->buckets == NULL) {
        free(new_table);
        return NULL;
    }
    return new_table;
}

void RobinHashTableClear(RobinHashTable_t **p_table,
                         void (*free_data)(void *), void (*free_key)(void *))
{
    assert(p_table != NULL);
    assert(*p_table != NULL);

    for (size_t i = 0; i < (*p_table)->count.max; i++) {
        if (free_data != NULL) {
            free_data((*p_table)->buckets[i]->data);
        }
        if (free_key != NULL) {
            free_key((*p_table)->buckets[i]->key);
        }
        free((*p_table)->buckets[i]);
    }
    free((*p_table)->buckets);
    free(*p_table);
    *p_table = NULL;
}

bool RobinHashTableAdd(RobinHashTable_t *table, void *key, void *data)
{
    assert(table != NULL);

    if (table->max_load == 0) {
        if (table->count.used >= table->count.max) {
            return false;
        }
    } else if ((float)table->count.used / table->count.max >= table->max_load
               || table->count.used >= table->count.max) {
        if (RobinHashTableRehash(table, 2 * table->count.max) == 0) {
            return false;
        }
    }
    RobinHTBucket_t *new_bucket = calloc(1, sizeof(RobinHTBucket_t));
    if (new_bucket == NULL) {
        return false;
    }
    new_bucket->data = data;
    new_bucket->key = key;
    size_t i = table->hash(key) % table->count.max;
    _addBucket(table->buckets, new_bucket, i, table->count.max);
    table->count.used += 1;
    return true;
}

void *RobinHashTableRemove(RobinHashTable_t *table, void *key,
                           void (*free_data)(void *), void (*free_key)(void *))
{
    assert(table != NULL);

    void *data = NULL;
    int found = 0;
    size_t curr_psl = 0;
    size_t i = table->hash(key) % table->count.max;
    while (table->buckets[i] != NULL && curr_psl <= table->buckets[i]->psl) {
        if (table->comp_key(table->buckets[i]->key, key) == 0) {
            data = table->buckets[i]->data;
            if (free_key != NULL) {
                free_key(table->buckets[i]->key);
            }
            free(table->buckets[i]);
            found = 1;
            break;
        }
        i = (i + 1) % table->count.max;
        curr_psl++;
    }
    if (found) {
        size_t prev_i = i;
        i = (i + 1) % table->count.max;
        while (table->buckets[i] != NULL && table->buckets[i]->psl > 0) {
            memcpy(&table->buckets[prev_i], &table->buckets[i],
                   sizeof(RobinHTBucket_t *));
            prev_i = i;
            i = (i + 1) % table->count.max;
        }
        table->buckets[prev_i] = NULL;
    }
    return data;
}

void *RobinHashTableFind(RobinHashTable_t *table, void *key)
{
    assert(table != NULL);

    void *data = NULL;
    size_t curr_psl = 0;
    size_t i = table->hash(key) % table->count.max;
    while (table->buckets[i] != NULL && curr_psl <= table->buckets[i]->psl) {
        if (table->comp_key(table->buckets[i]->key, key) == 0) {
            data = table->buckets[i]->data;
            break;
        }
        i = (i + 1) % table->count.max;
        curr_psl++;
    }
    return data;
}

int RobinHashTableRehash(RobinHashTable_t *table, size_t new_count)
{
    assert(table != NULL);

    float max_load = table->max_load;
    if (max_load == 0) {
        max_load = 1;
    }
    if ((float)new_count <= max_load * table->count.max) {
        return -1;
    }
    RobinHTBucket_t **new_buckets
        = calloc(new_count, sizeof(RobinHTBucket_t *));
    if (new_buckets == NULL) {
        return 0;
    }
    size_t rehash_count = 0;
    for (size_t i = 0;
         i < table->count.max && rehash_count <= table->count.used; i++) {
        if (table->buckets[i] != NULL) {
            size_t new_i = table->hash(table->buckets[i]->key) % new_count;
            _addBucket(new_buckets, table->buckets[i], new_i, new_count);
            rehash_count++;
        }
    }
    free(table->buckets);
    table->buckets = new_buckets;
    table->count.max = new_count;
    return 1;
}

static void _addBucket(RobinHTBucket_t **buckets,
                       RobinHTBucket_t *new_bucket, size_t i,
                       size_t max_count)
{
    RobinHTBucket_t *curr_bucket = new_bucket;
    for (; buckets[i] != NULL; i = (i + 1) % max_count) {
        if (curr_bucket->psl > buckets[i]->psl) {
            swap(&curr_bucket, &buckets[i], sizeof(RobinHTBucket_t *));
        }
        curr_bucket->psl += 1;
    }
    buckets[i] = curr_bucket;
}
