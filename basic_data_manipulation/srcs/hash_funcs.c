#include "hash_funcs.h"

unsigned long djb2_hash(const void *str)
{
    unsigned long hash = 5381;
    for(int i = 0; ((char*) str)[i] != '\0'; i++)
    {
        hash = ((hash << 5) + hash) + ((char*) str)[i]; /* hash*33 + c */
    }
    return hash;
}