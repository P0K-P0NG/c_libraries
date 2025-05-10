/**
 * @file universal_pointer.h
 * 
 * @brief 
 *   Struct for void pointers with associated type.
 * 
 * @author Sarutch Supaibulpipat (Pokpong) (8pokpong8@gmail.com)
 * @version 0.1
 * @date 2024-03-23
 */
#ifndef UNIVERSAL_POINTER_H
#define UNIVERSAL_POINTER_H

typedef struct typed_pointer
{
    void *const ptr;
    char type[5];
} Pointer;

#endif