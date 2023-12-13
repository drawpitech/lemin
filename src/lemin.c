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

static
void handle_anthill(anthill_t *anthill)
{
    room_t *graph;

    parse_me_baby(anthill);
    print_anthill(anthill);
    create_linked_list(anthill);
    graph = get_graph(anthill);
    if (graph == NULL)
        return;
    DEBUG("HEAD: %s", graph->name);
}

int lemin(void)
{
    anthill_t anthill = { 0 };

    handle_anthill(&anthill);
    free_ants(&anthill);
    return RET_VALID;
}
