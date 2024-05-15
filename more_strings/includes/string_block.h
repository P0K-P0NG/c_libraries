/**
 * @file string_block.h
 * 
 * @brief 
 *  struct for strings with explicit max length.
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2024-03-22
 */
#ifndef STRING_BLOCK_H
#define STRING_BLOCK_H

#include <stddef.h>

typedef struct string_block
{
    char *const items;
    const size_t len;
} String;

#endif