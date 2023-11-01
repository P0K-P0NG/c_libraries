/**
 * @file check_input.c
 * 
 * @brief 
 *  Functions for verifying characteristics about inputs from terminal.
 * 
 * @implements
 *  check_input.h
 * 
 * @author Pokpong
 * @version 0.1
 * @date 2023-02-25
 */
#include <string.h>
#include <ctype.h>
#include "check_input.h"

int str_is_alpha(const char str[])
{
    if(str == NULL)
    {
        return -1;
    }
    /* MAIN LOGIC */

    int is_alpha = 0;
    int i = 0;
    for(; str[i] != '\0'; i++)
    {
        if(!isalpha(str[i]))
        {
            break;
        }
    }
    if(str[i] == '\0' && i > 0)
    {
        is_alpha = 1;
    }
    return is_alpha;
}

int str_is_digit(const char str[])
{
    if(str == NULL)
    {
        return -1;
    }
    /* MAIN LOGIC */

    int i = 0;

    for(; str[i] != '\0'; i++)
    {
        if(str[i] < '0' || str[i] > '9')
        {
            i = 0;
            break;
        }
    }
    return i;
}

int str_is_int(const char str[])
{
    if(str == NULL)
    {
        return -1;
    }
    /* MAIN LOGIC */

    int is_num = 0;
    int i = 0;

    if(str[0] == '-')     // Check to skip negative sign
    {
        i++;
    }
    for(; str[i] != '\0'; i++)
    {
        if(isdigit(str[i]))
        {
            is_num = 1;
        }
        else
        {
            is_num = 0;
        }
    }
    return is_num*i;
}

int str_is_double(const char str[])
{
    if(str == NULL)
    {
        return -1;
    }
    /* MAIN LOGIC */
    
    int deci_pt_count = 0;
    int is_num = 0;
    int i = 0;

    if(str[0] == '-')   // Check to skip negative sign
    {
        i++;
    }
    for(; str[i] != '\0'; i++)
    {
        if(str[i] == '.')
        {
            deci_pt_count++;
            if(deci_pt_count > 1)
            {
                is_num = 0;
                break;
            }
        }
        else if(isdigit(str[i]))
        {
            is_num = 1;
        }
        else
        {
            is_num = 0;
            break;
        }
    }
    return is_num*i;
}

int has_suffix(const char str[], const char suffix[])
{
    if(str == NULL || suffix == NULL)
    {
        return -1;
    }
    /* MAIN LOGIC */
    
    int result = 0;
    int suffix_start = strlen(str) - strlen(suffix);
    if(suffix_start >= 0 && strcmp(&str[suffix_start], suffix) == 0)
    {
        result = 1;
    }
    return result;
}