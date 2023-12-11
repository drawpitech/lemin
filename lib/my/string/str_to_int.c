/*
** EPITECH PROJECT, 2023
** lemin
** File description:
** str_to_int
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
bool is_valid(char c, bool has_started, bool *is_neg, const char *base)
{
    if (index_in(c, base) != -1)
        return true;
    if (c == '+')
        return !(has_started);
    if (c == '-') {
        if (has_started)
            return false;
        *is_neg = !*is_neg;
        return true;
    }
    if (has_started)
        return false;
    return false;
}

static
int64_t true_val(int64_t res, bool is_neg)
{
    if (is_neg)
        return res;
    res = -res;
    if (res < 0)
        return 0;
    return res;
}

int64_t str_to_int_base(char const *str, char const *base)
{
    int64_t res = 0;
    bool is_neg = false;
    bool has_started = false;
    int len = (int)my_strlen(base);

    if (str == NULL || base == 0)
        return INT64_MAX;
    for (int i = 0; str[i]; i++) {
        if (!is_valid(str[i], has_started, &is_neg, base))
            return (index_in(str[i], base) == -1)
                ? INT64_MAX
                : true_val(res, is_neg);
        if (index_in(str[i], base) == -1)
            continue;
        has_started = true;
        res = res * len + -index_in(str[i], base);
        if (res > 0)
            return INT64_MAX;
    }
    return true_val(res, is_neg);
}

int64_t str_to_int(char const *str)
{
    return str_to_int_base(str, BASE_DEC);
}
