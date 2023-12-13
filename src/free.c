/*
** EPITECH PROJECT, 2023
** lemin
** File description:
** free
*/

#include <stdlib.h>

#include "lemin.h"

static
void free_room(room_t *room)
{
    free(room->name);
    if (room->leaves.arr != NULL)
        free(room->leaves.arr);
}

void free_ants(anthill_t *anthill)
{
    if (anthill == NULL)
        return;
    if (anthill->rooms.rooms != NULL) {
        for (size_t i = 0; i < anthill->rooms.count; i++)
            free_room(anthill->rooms.rooms + i);
        free(anthill->rooms.rooms);
    }
    if (anthill->tunnels.tunnels != NULL) {
        for (size_t i = 0; i < anthill->tunnels.count; i++)
            free(anthill->tunnels.tunnels[i].from);
        free(anthill->tunnels.tunnels);
    }
}
