/*
** EPITECH PROJECT, 2023
** lemin
** File description:
** lemin
*/

#include <stdio.h>

#include "my/debug.h"
#include "my/std.h"
#include "my/string.h"

#include "lemin.h"

static
void sanitize(char *line)
{
    char *tmp = my_strfind(line, '\n');

    if (tmp == NULL)
        return;
    *tmp = '\0';
}

static
void free_ants(anthill_t *anthill)
{
    if (anthill->rooms.rooms != NULL) {
        for (size_t i = 0; i < anthill->rooms.count; i++)
            free(anthill->rooms.rooms[i].name);
        free(anthill->rooms.rooms);
    }
    if (anthill->tunnels.tunnels != NULL) {
        for (size_t i = 0; i < anthill->tunnels.count; i++)
            free(anthill->tunnels.tunnels[i].from);
        free(anthill->tunnels.tunnels);
    }
}

int lemin(void)
{
    size_t size = 0;
    char *buffer = NULL;
    anthill_t anthill = { 0 };
    int ret = RET_VALID;

    while (getline(&buffer, &size, stdin) != -1) {
        sanitize(buffer);
        DEBUG("-> [%s]", buffer);
        ret = process_line(buffer, &anthill);
        if (ret == RET_ERROR)
            break;
    }
    if (buffer != NULL)
        free(buffer);
    free_ants(&anthill);
    return ret;
}
