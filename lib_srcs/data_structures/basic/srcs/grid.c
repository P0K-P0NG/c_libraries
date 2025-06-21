/**
 * @file grid.c
 *
 * @brief
 *  Struct and functions for a grid or 2D array.
 *
 * @implements
 *  grid.h
 *
 * @author Sarutch Supaibulpipat (Pokpong) (8pokpong8@gmail.com)
 * @version 0.1
 * @date 2025-06-17
 */
#include "grid.h"
#include <assert.h>
#include <stdlib.h>

Grid_t *GridCreate(size_t row_count, size_t col_count)
{
    Grid_t *new_grid = calloc(1, sizeof(Grid_t));
    if (new_grid == NULL)
        return NULL;
    new_grid->items = calloc(row_count * col_count, sizeof(void *));
    if (new_grid->items == NULL) {
        free(new_grid);
        return NULL;
    }
    new_grid->row_count = row_count;
    new_grid->col_count = col_count;
    return new_grid;
}

void GridClear(Grid_t **p_grid, void (*free_data)(void *))
{
    assert(p_grid != NULL);
    assert(*p_grid != NULL);

    if (free_data != NULL) {
        size_t len = (*p_grid)->row_count * (*p_grid)->col_count;
        for (size_t i = 0; i < len; i++) {
            free_data((*p_grid)->items[i]);
        }
    }
    free((*p_grid)->items);
    free(*p_grid);
    *p_grid = NULL;
}

bool GridSet(Grid_t *grid, size_t row_idx, size_t col_idx, void *data,
             void (*free_data)(void *))
{
    assert(grid != NULL);

    if (col_idx < grid->col_count && row_idx < grid->row_count) {
        size_t idx = row_idx + col_idx * grid->row_count;
        if (free_data != NULL && grid->items[idx] != NULL)
            free_data(grid->items[idx]);
        grid->items[idx] = data;
        return true;
    } else {
        return false;
    }
}

void *GridGet(Grid_t *grid, size_t row_idx, size_t col_idx)
{
    assert(grid != NULL);

    if (col_idx < grid->col_count && row_idx < grid->row_count) {
        return grid->items[row_idx + col_idx * grid->row_count];
    } else {
        return NULL;
    }
}