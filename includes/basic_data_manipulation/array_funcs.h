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
 * @param value         item or value to find
 * @param arr           array to search through
 * @param item_size     size of the items in the array in bytes 
 * @param count         number of items in the array
 * @param comp_func     function compare the items
 * 
 * @return the index of the item in the array. -1 if not found
 */
int get_arr_idx(const void *value, const void *arr, size_t item_size, int count, int (*comp_func)(const void*, const void*));

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
 * @param arr           array to search through
 * @param item_size     size of the items in the array in bytes 
 * @param count         number of items in the array
 * @param comp_func     function compare the items
 */
void insert_sort_arr(void *arr, size_t item_size, int count, int (*comp_func)(const void*, const void*));
#endif