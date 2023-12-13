/*
** EPITECH PROJECT, 2023
** lemin
** File description:
** move
*/

#include <stdlib.h>

#include "lemin.h"

#include "my/string.h"

static
tunnel_t *get_shorest_path(room_t *graph, anthill_t *anthill)
{
    tunnel_t *shortest = malloc(anthill->rooms.count * sizeof(tunnel_t));

    if (shortest == NULL)
        return NULL;
    my_memset(shortest, 0, anthill->rooms.count * sizeof(tunnel_t));
    return shortest;
}

void move_ants(room_t *graph, anthill_t *anthill)
{
    tunnel_t *shortest;

    if (graph == NULL || anthill == NULL)
        return;
    shortest = get_shorest_path(graph, anthill);
    if (shortest == NULL)
        return;
    free(shortest);
}
