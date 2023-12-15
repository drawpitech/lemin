/*
** EPITECH PROJECT, 2023
** lemin
** File description:
** convert_base
*/

#include "string.h"

char *convert_base(char const *nbr, char const *base_from, char const *base_to)
{
    return my_nbr_to_base(my_strtol_base(nbr, NULL, base_from), base_to);
}
