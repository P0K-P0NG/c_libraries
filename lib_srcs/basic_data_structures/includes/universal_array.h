#ifndef UNIVERSAL_ARRAY_H
#define UNIVERSAL_ARRAY_H

#include <stdbool.h>
#include <stddef.h>

#define TYPE_LEN 5

struct Array {
    void *items;
    size_t item_size;
    size_t len;
};

#define IDX(type, arr, i) (*(type *)((arr).items + (i) * (arr).item_size))
#define ArrayStackInit(items, item_size, len)                                  \
    ((struct Array){(void *)items, (item_size), (len)})
#define ArrayItemsStackInit(type, len, ...) ((type[len]){__VA_ARGS__})

extern struct Array *ArrayCreate(size_t item_size, size_t len);

extern void ArrayClear(struct Array **p_arr);

extern void ArraySet(struct Array *arr, size_t idx, void *item);

extern void *ArrayGet(struct Array *arr, size_t idx);

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
 * @param comp_func     function compare the items
 */
extern bool ArrayInsertSort(struct Array *arr,
                            int (*comp_func)(const void *, const void *));

extern int ArrayToInt(struct Array *arr);

#endif