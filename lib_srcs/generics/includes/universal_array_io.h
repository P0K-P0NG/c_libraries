
/**
 * @file universal_array_io.h
 *
 * @brief
 *
 * @author Sarutch Supaibulpipat (Pokpong) (8pokpong8@gmail.com)
 * @version 0.1
 * @date 2024-03-24
 */
#ifndef UNIVERSAL_ARRAY_IO_H
#define UNIVERSAL_ARRAY_IO_H

#include "result_struct.h"
#include "universal_array.h"
#include <stdio.h>

extern int ArrayReadBinary(struct Array *arr, FILE *file_src);

extern int ArrayWriteBinary(struct Array arr, FILE *file_dest);

extern int ArrayWrite(struct Array arr, char type[TYPE_LEN], char *delim,
                      FILE *file_dest);

#endif