/*
** EPITECH PROJECT, 2023
** lemin
** File description:
** test_generator
*/

#include "../src/lemin.h"
#include <stdio.h>
#include <stdlib.h>

static
void print_rooms(long size)
{
    long home = rand() % size;
    long end = rand() % size;

    for (; end == home; end = rand() % size);
    for (long i = 0; i < size; i++) {
        if (i == home)
            printf("##start\n");
        if (i == end)
            printf("##end\n");
        printf("%ld %ld %ld\n", i, rand() % (10 * size), rand() % (10 * size));
    }
}

static
void print_tunnels(long size, long density)
{
    for (long x = 0; x < (size * size); x++)
        if (density > rand() % 100)
            printf("%ld-%ld\n", x / size, x % size);
}

int main(int argc, char **argv)
{
    const int base_ten = 10;
    long size = strtol(argv[1], NULL, base_ten);
    long density = strtol(argv[2], NULL, base_ten);
    long nb = strtol(argv[3], NULL, base_ten);

    srand(0);
    if (argc != 4)
        return EXIT_FAILURE;
    printf("%ld\n", nb);
    print_rooms(size);
    print_tunnels(size, density);
    return EXIT_SUCCESS;
}
