#ifndef TEXT_TABLE_H
#define TEXT_TABLE_H

#include "doubly_linked_list.h"

struct TextRow {};

struct TextColumn {};

struct TextTable {
    struct DLList cols;
    struct DLList rows;
};

#endif