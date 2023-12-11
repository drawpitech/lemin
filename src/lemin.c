/*
** EPITECH PROJECT, 2023
** lemin
** File description:
** lemin
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "my/io.h"

#include "lemin.h"

int lemin(void)
{
    size_t size = 0;
    char *buffer = NULL;

    while (getline(&buffer, &size, stdin) != -1) {
        buffer[size] = '\0';
        my_printf("%s", buffer);
    }
    if (buffer != NULL)
        free(buffer);
    return EXIT_SUCCESS;
}
