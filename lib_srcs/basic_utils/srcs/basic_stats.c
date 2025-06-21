#include "basic_stats.h"

int maxInt(const int num1, const int num2)
{
    return (num1 > num2) ? num1 : num2;
}

int minInt(const int num1, const int num2)
{
    return (num1 < num2) ? num1 : num2;
}

float maxFloat(const float num1, const float num2)
{
    return (num1 > num2) ? num1 : num2;
}

float minFloat(const float num1, const float num2)
{
    return (num1 < num2) ? num1 : num2;
}

double maxDouble(const double num1, const double num2)
{
    return (num1 > num2) ? num1 : num2;
}

double minDouble(const double num1, const double num2)
{
    return (num1 < num2) ? num1 : num2;
}

size_t sumSizeT(const size_t *arr, size_t count)
{
    size_t sum = 0;
    for (size_t i = 0; i < count; i++)
        sum += arr[i];
    return sum;
}