
/**
 * @file universal_array_io.h
 *
 * @brief
 *  Streaming function for the Array_t type.
 *
 * @author Sarutch Supaibulpipat (Pokpong) (8pokpong8@gmail.com)
 * @version 0.1
 * @date 2024-03-24
 */
#ifndef UNIVERSAL_ARRAY_IO_H
#define UNIVERSAL_ARRAY_IO_H

#include "result_struct.h"
#include "universal_array.h"
#include <stdbool.h>
#include <stdio.h>

extern bool ArrayReadBinary(Array_t **p_arr, FILE *file_src);

extern bool ArrayWriteBinary(Array_t *arr, FILE *file_dest);

extern bool ArrayWrite(Array_t *arr, const char *type_format,
                       const char *delim, FILE *file_dest);

#endif