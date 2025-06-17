#ifndef HASH_FUNCS_H
#define HASH_FUNCS_H

#include <stddef.h>

/**
 * @brief
 *  hash function for strings using the djb2 algorithm.
 *
 * @param[in] str   string to hash
 *
 * @return hashed index
 */
size_t djb2Hash(const void *str);

#endif