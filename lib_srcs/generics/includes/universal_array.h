#ifndef UNIVERSAL_ARRAY_H
#define UNIVERSAL_ARRAY_H

#include <stddef.h>

#define TYPE_LEN 5

// union ArrayDataBase
// {
//     char char_u;
//     short short_u;
//     int int_u;
//     long long_u;
//     float float_u;
//     double double_u;
// };

// #ifndef REDEFINE_ARRAY_DATA_UNION
//     typedef union ArrayDataBase ArrayData;
// #endif

struct Array {
    void *items;
    size_t item_size;
    unsigned int len;
};

#define IDX(type, arr, i) (*(type *)((arr).items + (i) * (arr).item_size))
#define ArrayInit(items, item_size, len)                                       \
    ((struct Array){(void *)items, (item_size), (len)})
#define ArrayItemsInit(type, len, ...) ((type[len]){__VA_ARGS__})

extern void ArraySetItem(struct Array arr, unsigned int idx, void *item);

void *ArrayGetItem(struct Array arr, unsigned int idx);

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
 * @param arr           array to search through
 * @param item         item or value to find
 * @param comp_func     function compare the items
 *
 * @return the index of the item in the array. -1 if not found
 */
extern int ArrayGetIdx(struct Array arr, const void *item,
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
extern void ArrayInsertSort(struct Array *arr,
                            int (*comp_func)(const void *, const void *));

extern int ArrayToInt(struct Array arr);

#endif