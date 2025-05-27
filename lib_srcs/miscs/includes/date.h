
/**
 * @file date.h
 *
 * @brief
 *  Structs and functions dates.
 *
 * @author Pokpong
 * @version 0.1
 * @date 2023-05-15
 */
#ifndef DATE_H
#define DATE_H

extern const int days_in_month[12];
extern const char month_names[12][10];

struct Date {
    int day;   // range depends on the month and year
    int month; // 1-12
    int year;  // defined by the user
};

/**
 * @brief
 *  Check if a date is valid.
 *
 * @param[in] date      date to check
 * @param[in] min_year  minimum year bound
 * @param[in] max_year  maximum year bound
 *
 * @return 1 if is valid; 0 if is not valid.
 */
extern int checkDate(struct Date date, int min_year, int max_year);
#endif