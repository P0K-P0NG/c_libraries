/**
 * @file pointer_array.h
 * 
 * @brief 
 *  Struct and functions for flexible pointer array.
 * 
 * @author Sarutch Supaibulpipat (Pokpong) (8pokpong8@gmail.com)
 * @version 0.1
 * @date 2025-06-17
 */
#ifndef POINTER_ARRAY_H
#define POINTER_ARRAY_H

#include <stdbool.h>
#include <stddef.h>

typedef struct PointerArray {
    void **ptrs;
    size_t len;
} PointerArray_t;

/**
 * @brief
 *  Creates a pointer array struct
 *
 * @param[in] len   length of array
 *
 * @return Pointer to the array of pointers. NULL if memory allocation failed.
 */
extern PointerArray_t *PointerArrayCreate(size_t len);

/**
 * @brief
 *  Deletes a pointer array struct and frees the data of the pointer if provided
 *  with a function to do so.
 *
 * @param[in,out] p_arr         pointer array to delete
 * @param[in]     free_data     function to free data in the pointers
 */
extern void PointerArrayClear(PointerArray_t **p_arr,
                              void (*free_data)(void *data));

/**
 * @brief
 *  Gets the pointer at the specific index in a pointer array struct.
 *
 * @param[in] arr   pointer array retrieve from
 * @param[in] idx   idx to retrieve
 * 
 * @return Pointer at the specificed index. NULL if index is out of bounds.
 */
extern void *PointerArrayGet(PointerArray_t *arr, size_t idx);

/**
 * @brief  
 *  Gets the pointer at the specific index in a pointer array struct and frees
 *  the data of replaced pointer if given the function to do so.
 *
 * @param[in,out] arr           pointer array to set
 * @param[in]     idx           idx to set
 * @param[in]     data          pointer to data to set
 * @param[in]     free_data     function to free old pointer
 * 
 * @return true  : pointer set sucessfully
 * @return false : index out of bounds
 */
extern bool PointerArraySet(PointerArray_t *arr, size_t idx, void *data,
                            void (*free_data)(void *data));

#endif