/*
** EPITECH PROJECT, 2023
** lemin
** File description:
** move
*/

#include <stdlib.h>

#include "my/std.h"
#include "my/debug.h"
#include "my/math.h"
#include "my/string.h"

#include "lemin.h"

static
int visit_room(room_t **shortest, size_t i, room_t *graph)
{
    if (graph == NULL || graph->visited == true)
        return RET_ERROR;
    graph->visited = true;
    if (graph->type == ROOM_EXIT) {
        shortest[i] = graph;
        return RET_VALID;
    }
    for (size_t j = 0; j < graph->leaves.n; j++) {
        if (visit_room(shortest, i + 1, graph->leaves.arr[j]) == RET_ERROR)
            continue;
        shortest[i] = graph;
        return RET_VALID;
    }
    return RET_ERROR;
}

static
room_t **get_shorest_path(room_t *graph, anthill_t *anthill)
{
    size_t size = anthill->rooms.count * sizeof(tunnel_t);
    room_t **shortest = malloc(size);

    if (shortest == NULL)
        return NULL;
    my_memset(shortest, 0, size);
    if (visit_room(shortest, 0, graph) == RET_VALID)
        return shortest;
    free(shortest);
    return NULL;
}

static
void single_file(
    anthill_t *anthill, size_t *positions,
    size_t len_shortest, room_t *shortest[len_shortest])
{
    bool space = false;

    for (size_t i = 0; i < anthill->ants; i++) {
        if (positions[i] == len_shortest - 1)
            continue;
        positions[i] += 1;
        my_printf("%sP%d-%s", (space) ? " " : "",
            i + 1, shortest[positions[i]]->name);
        space = true;
        if (positions[i] == 1)
            break;
    }
    my_printf("\n");
}

static
void move_my_children(anthill_t *anthill, room_t **shortest)
{
    size_t positions[anthill->ants];
    size_t len_shortest;

    for (size_t i = 0; i < anthill->ants; i++)
        positions[i] = 0;
    for (len_shortest = 0; shortest[len_shortest] != NULL; len_shortest++);
    do {
        single_file(anthill, positions, len_shortest, shortest);
    } while (positions[anthill->ants - 1] != len_shortest - 1);
}

void move_ants(room_t *graph, anthill_t *anthill)
{
    room_t **shortest;

    if (graph == NULL || anthill == NULL)
        return;
    shortest = get_shorest_path(graph, anthill);
    if (shortest == NULL)
        return;
    my_printf("#moves\n");
    for (size_t i = 0; shortest[i] != NULL; i++)
        DEBUG("move %d: %s", i + 1, shortest[i]->name);
    move_my_children(anthill, shortest);
    free(shortest);
}
