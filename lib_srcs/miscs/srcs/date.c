/**
 * @file date.c
 *
 * @brief
 *  Structs and functions dates.
 *
 * @implements
 *  date.h
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-15
 */
#include "date.h"

const int month_len[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const char month_names[12][10]
    = {"January", "Febuary", "March",     "April",    "May",     "June",
       "July",    "August",  "September", "November", "December"};

int checkDate(struct Date date, int min_year, int max_year)
{
    int is_valid = 0;
    int offset = 0;

    // check for febuary of a leap year
    if (date.month == 2 && date.year % 4 == 0
        && !(date.year % 100 == 0 && date.year % 400 != 0)) {
        offset = 1;
    }

    if (date.year >= min_year && date.year <= max_year && date.month >= 1
        && date.month <= 12 && date.day >= 1
        && date.day <= month_len[date.month - 1] + offset) {
        is_valid = 1;
    }
    return is_valid;
}