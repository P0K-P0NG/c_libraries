/**
 * @file universal_array.h
 * 
 * @brief 
 *  Struct and functions of an universal array type.
 * 
 * @author Sarutch Supaibulpipat (Pokpong) (8pokpong8@gmail.com)
 * @version 0.1
 * @date 2025-06-17
 */
#ifndef UNIVERSAL_ARRAY_H
#define UNIVERSAL_ARRAY_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Array {
    void *items;
    size_t item_size;
    size_t len;
} Array_t;

#define IDX(type, arr, i) (*(type *)((arr).items + (i) * (arr).item_size))
#define ArrayStackInit(items, item_size, len)                                  \
    ((Array_t){(void *)items, (item_size), (len)})
#define ArrayItemsStackInit(type, len, ...) ((type[len]){__VA_ARGS__})

/**
 * @brief
 *  Creates an array struct.
 *
 * @param[in] item_size     size of an item
 * @param[in] len           length of array
 * 
 * @return Pointer to new array, NULL if memory allocation failed.
 */
extern Array_t *ArrayCreate(size_t item_size, size_t len);

/**
 * @brief 
 *  Deletes an array struct.
 * 
 * @param p_arr     array to delete
 */
extern void ArrayClear(Array_t **p_arr);

/**
 * @brief 
 *  Sets the value of an item in an array struct at the speficied index.
 * 
 * @param arr   array to set
 * @param idx   index to set
 * @param item  value to set
 */
extern void ArraySet(Array_t *arr, size_t idx, void *item);

/**
 * @brief 
 *  Gets the value of an item in an array struct at the speficied index.
 * 
 * @param arr   array to retrieve
 * @param idx   index to retrieve
 * 
 * @return Pointer to the retrieve value. 
 */
extern void *ArrayGet(Array_t *arr, size_t idx);

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
 * @param[in]  arr          array to search through
 * @param[out] idx          variable to store the index
 * @param[in]  item         item or value to find
 * @param[in]  comp_func    function compare the items
 *
 * @return
 *  true  : item is found
 *  false : item is not found
 */
extern bool ArrayFind(struct Array *arr, size_t *idx, const void *item,
                      int (*comp_func)(const void *, const void *));

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
 * @param[in,out] arr           array to sort
 * @param[in]     comp_func     function compare the items
 */
extern bool ArrayInsertSort(Array_t *arr,
                            int (*comp_func)(const void *, const void *));

extern int ArrayToInt(Array_t *arr);

#endif