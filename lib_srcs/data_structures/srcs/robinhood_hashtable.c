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
#include <stdlib.h>
#include <string.h>

void RobinHashTableAddBucket(struct RobinHTBucket **buckets,
                             struct RobinHTBucket *new_bucket, unsigned long i,
                             unsigned long max_count);

struct RobinHashTable *RobinHashTableCreate(unsigned long bucket_count,
                                            float max_load_prop)
{
    struct RobinHashTable *new_table = calloc(1, sizeof(struct RobinHashTable));
    if (new_table == NULL) {
        return NULL;
    }
    new_table->count.max = bucket_count;
    new_table->max_load = max_load_prop;
    new_table->buckets = calloc(bucket_count, sizeof(struct RobinHTBucket *));
    if (new_table->buckets == NULL) {
        free(new_table);
        return NULL;
    }
    return new_table;
}

void RobinHashTableClear(struct RobinHashTable **table,
                         void (*free_key)(void *), void (*free_data)(void *))
{
    for (unsigned long i = 0; i < (*table)->count.max; i++) {
        if (free_data != NULL) {
            free_data((*table)->buckets[i]->data);
        }
        if (free_key != NULL) {
            free_key((*table)->buckets[i]->key);
        }
        free((*table)->buckets[i]);
    }
    free((*table)->buckets);
    free(*table);
    *table = NULL;
}

int RobinHashTableAdd(struct RobinHashTable *table, void *key, void *data,
                      unsigned long (*hash_func)(const void *))
{
    if (table->max_load == 0) {
        if (table->count.used >= table->count.max) {
            return 0;
        }
    } else if ((float)table->count.used / table->count.max >= table->max_load
               || table->count.used >= table->count.max) {
        if (RobinHashTableRehash(table, 2 * table->count.max, hash_func) == 0) {
            return 0;
        }
    }
    struct RobinHTBucket *new_bucket = calloc(1, sizeof(struct RobinHTBucket));
    if (new_bucket == NULL) {
        return 0;
    }
    new_bucket->data = data;
    new_bucket->key = key;
    unsigned long i = hash_func(key) % table->count.max;
    RobinHashTableAddBucket(table->buckets, new_bucket, i, table->count.max);
    table->count.used += 1;
    return 1;
}

void RobinHashTableAddBucket(struct RobinHTBucket **buckets,
                             struct RobinHTBucket *new_bucket, unsigned long i,
                             unsigned long max_count)
{
    struct RobinHTBucket *curr_bucket = new_bucket;
    for (; buckets[i] != NULL; i = (i + 1) % max_count) {
        if (curr_bucket->psl > buckets[i]->psl) {
            swap(&curr_bucket, &buckets[i], sizeof(struct RobinHTBucket *));
        }
        curr_bucket->psl += 1;
    }
    buckets[i] = curr_bucket;
}

void *RobinHashTableRemove(struct RobinHashTable *table, void *key,
                           unsigned long (*hash_func)(const void *),
                           int (*comp_key)(const void *, const void *),
                           void (*free_key)(void *))
{
    void *data = NULL;
    int found = 0;
    unsigned long curr_psl = 0;
    unsigned long i = hash_func(key) % table->count.max;
    while (table->buckets[i] != NULL && curr_psl <= table->buckets[i]->psl) {
        if (comp_key(table->buckets[i]->key, key) == 0) {
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
        unsigned long prev_i = i;
        i = (i + 1) % table->count.max;
        while (table->buckets[i] != NULL && table->buckets[i]->psl > 0) {
            memcpy(&table->buckets[prev_i], &table->buckets[i],
                   sizeof(struct RobinHTBucket *));
            prev_i = i;
            i = (i + 1) % table->count.max;
        }
        table->buckets[prev_i] = NULL;
    }
    return data;
}

void *RobinHashTableFind(struct RobinHashTable *table, void *key,
                         unsigned long (*hash_func)(const void *),
                         int (*comp_key)(const void *, const void *))
{
    void *data = NULL;
    unsigned long curr_psl = 0;
    unsigned long i = hash_func(key) % table->count.max;
    while (table->buckets[i] != NULL && curr_psl <= table->buckets[i]->psl) {
        if (comp_key(table->buckets[i]->key, key) == 0) {
            data = table->buckets[i]->data;
            break;
        }
        i = (i + 1) % table->count.max;
        curr_psl++;
    }
    return data;
}

int RobinHashTableRehash(struct RobinHashTable *table, unsigned long new_count,
                         unsigned long (*hash_func)(const void *))
{
    float max_load = table->max_load;
    if (max_load == 0) {
        max_load = 1;
    }
    if ((float)new_count <= max_load * table->count.max) {
        return -1;
    }
    struct RobinHTBucket **new_buckets
        = calloc(new_count, sizeof(struct RobinHTBucket *));
    if (new_buckets == NULL) {
        return 0;
    }
    unsigned long rehash_count = 0;
    for (unsigned long i = 0;
         i < table->count.max && rehash_count <= table->count.used; i++) {
        if (table->buckets[i] != NULL) {
            unsigned long new_i = hash_func(table->buckets[i]->key) % new_count;
            RobinHashTableAddBucket(new_buckets, table->buckets[i], new_i,
                                    new_count);
            rehash_count++;
        }
    }
    free(table->buckets);
    table->buckets = new_buckets;
    table->count.max = new_count;
    return 1;
}
