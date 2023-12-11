/*
** EPITECH PROJECT, 2023
** lemin
** File description:
** get_color
*/

#include "std.h"

int get_color(unsigned char red, unsigned char green, unsigned char blue)
{
    return (red << 16) + (green << 8) + blue;
}
