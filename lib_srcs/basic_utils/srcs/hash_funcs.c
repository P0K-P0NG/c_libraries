#include "hash_funcs.h"

size_t djb2Hash(const void *str)
{
    size_t hash = 5381;
    for (size_t i = 0; ((char *)str)[i] != '\0'; i++) {
        hash = ((hash << 5) + hash) + ((char *)str)[i]; /* hash*33 + c */
    }
    return hash;
}