/**
 * @file array_funcs.h
 * 
 * @brief 
 *  Functions for sorting data.
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-02-25
 */
#ifndef ARRAY_FUNCS_H
#define ARRAY_FUNCS_H

#include <stddef.h>

/**
 * @brief 
 *  Finds the array index of a item.
 * 
 * @note
 *  The function used to compare must behave in the follows 
 *  ways in order for the function to perform properly. @n
 *  1) WHEN input_1 > input_2,  RETURNS a postive integer @n
 *  2) WHEN input_1 < input_2,  RETURNS a negative integer @n
 *  3) WHEN input_1 == input_2, RETURNS zero @n
 * 
 * @param[in] value         item or value to find
 * @param[in] arr           array to search through
 * @param[in] item_size     size of the items in the array in bytes 
 * @param[in] count         number of items in the array
 * @param[in] comp_func     function compare the items
 * 
 * @return the index of the item in the array. -1 if not found
 */
extern int getArrIdx(const void *value, const void *arr, size_t item_size, int count, int (*comp_func)(const void*, const void*));

/**
 * @brief 
 *  Sorts an array using insertion sort
 * 
 * @note
 *  The function used to compare must behave in the follows 
 *  ways in order for the function to perform properly. @n
 *  1) WHEN input_1 > input_2,  RETURNS a postive integer @n
 *  2) WHEN input_1 < input_2,  RETURNS a negative integer @n
 *  3) WHEN input_1 == input_2, RETURNS zero @n
 * 
 * @param[in] arr           array to search through
 * @param[in] item_size     size of the items in the array in bytes 
 * @param[in] count         number of items in the array
 * @param[in] comp_func     function compare the items
 */
extern void insertSortArr(void *arr, size_t item_size, int count, int (*comp_func)(const void*, const void*));
#endif