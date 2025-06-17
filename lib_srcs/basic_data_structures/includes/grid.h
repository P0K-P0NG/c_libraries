/**
 * @file grid.h
 * 
 * @brief 
 *  Struct and functions for a grid or 2D array.
 * 
 * @author Sarutch Supaibulpipat (Pokpong) (8pokpong8@gmail.com)
 * @version 0.1
 * @date 2025-06-17
 */
#ifndef GRID_H
#define GRID_H

#include <stdbool.h>
#include <stddef.h>

struct Grid {
    void **items;
    size_t row_count;
    size_t col_count;
};

extern struct Grid *GridCreate(size_t row_count, size_t col_count);
extern void GridClear(struct Grid **p_grid, void (*free_data)(void *));
extern bool GridSet(struct Grid *grid, size_t row_idx, size_t col_idx,
                    void *data);
extern void *GridGet(struct Grid *grid, size_t row_idx, size_t col_idx);
#endif