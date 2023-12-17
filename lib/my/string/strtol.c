/*
** EPITECH PROJECT, 2023
** lemin
** File description:
** strtol
*/

#include "string.h"

static
int index_in(char c, char const *base)
{
    for (int i = 0; base[i]; i++)
        if (base[i] == c)
            return i;
    return -1;
}

static
bool is_valid(char c, bool *negative, const char *base)
{
    if (index_in(c, base) != -1)
        return true;
    if (c == '+')
        return true;
    if (c == '-') {
        *negative = !*negative;
        return true;
    }
    return false;
}

long my_strtol_base(const char *str, char const *base)
{
    long res = 0;
    long len = (long)my_strlen(base);
    bool negative = false;
    size_t i = 0;

    if (str == NULL || base == 0)
        return INT64_MAX;
    for (; str[i]; i++) {
        if (!is_valid(str[i], &negative, base))
            break;
        if (index_in(str[i], base) == -1)
            continue;
        res = res * len + -index_in(str[i], base);
    }
    if (str[i])
        return INT64_MAX;
    return (negative) ? res : -res;
}

long my_strtol(const char *str)
{
    return my_strtol_base(str, BASE_DEC);
}
