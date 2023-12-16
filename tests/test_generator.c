/*
** EPITECH PROJECT, 2023
** lemin
** File description:
** tests for generator
*/

#include <stdio.h>
#include <stdlib.h>

#include "test.h"

static
void print_rooms(long size)
{
    const int coef = 10;
    long home = rand() % size;
    long end = rand() % size;

    for (; end == home; end = rand() % size);
    for (long i = 0; i < size; i++) {
        if (i == home)
            printf("##start\n");
        if (i == end)
            printf("##end\n");
        printf("%ld %ld %ld\n",
            i,
            rand() % (coef * size),
            rand() % (coef * size));
    }
}

static
void print_tunnels(long size, long density)
{
    const int coef = 100;

    for (long x = 0; x < (size * size); x++)
        if (density > rand() % coef)
            printf("%ld-%ld\n", x / size, x % size);
}

int main(int argc, char **argv)
{
    const int base_ten = 10;
    long density;
    long size;
    long nb;

    srand(0);
    if (argc != 4) {
        printf("%s", USAGE);
        return EXIT_SUCCESS;
    }
    size = strtol(argv[1], NULL, base_ten);
    density = strtol(argv[2], NULL, base_ten);
    nb = strtol(argv[3], NULL, base_ten);
    printf("%ld\n", nb);
    print_rooms(size);
    print_tunnels(size, density);
    return EXIT_SUCCESS;
}
