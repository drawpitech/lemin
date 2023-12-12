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

static
void print_room(room_t const *room)
{
    if (room->type == ROOM_ENTRANCE)
        my_printf("##start\n");
    if (room->type == ROOM_EXIT)
        my_printf("##end\n");
    my_printf("%s %d %d\n", room->name, room->x, room->y);
}

static
void print_anthill(anthill_t *anthill)
{
    tunnel_t *tunnel;

    my_printf("#number_of_ants\n%d\n", anthill->ants);
    if (anthill->rooms.rooms != NULL) {
        my_printf("#rooms\n");
        for (size_t i = 0; i < anthill->rooms.count; i++)
            print_room(anthill->rooms.rooms + i);
    }
    if (anthill->tunnels.tunnels != NULL) {
        my_printf("#tunnels\n");
        for (size_t i = 0; i < anthill->tunnels.count; i++) {
            tunnel = anthill->tunnels.tunnels + i;
            my_printf("%s-%s\n", tunnel->from, tunnel->to);
        }
    }
}

int lemin(void)
{
    anthill_t anthill = { 0 };

    parse_me_baby(&anthill);
    print_anthill(&anthill);
    free_ants(&anthill);
    return RET_VALID;
}
