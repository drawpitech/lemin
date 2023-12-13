/*
** EPITECH PROJECT, 2023
** lemin
** File description:
** linked
*/

#include "my/debug.h"
#include "my/std.h"

#include "lemin.h"
#include "my/string.h"

static
room_t *find_room(anthill_t *anthill, char const *name)
{
    for (size_t i = 0; i < anthill->rooms.count; i++)
        if (my_strcmp(anthill->rooms.rooms[i].name, name) == 0)
            return anthill->rooms.rooms + i;
    return NULL;
}

static
void add_tunnel(anthill_t *anthill, tunnel_t *tunnel)
{
    room_t *from = find_room(anthill, tunnel->from);
    room_t *to = find_room(anthill, tunnel->to);
    room_t **tmp;

    if (from == NULL || to == NULL)
        return;
    tmp = my_reallocarray(
        from->leaves.arr, from->leaves.n + 1,
        from->leaves.n, sizeof(room_t *)
    );
    if (tmp == NULL)
        return;
    from->leaves.arr = tmp;
    from->leaves.arr[from->leaves.n] = to;
    from->leaves.n += 1;
}

void create_linked_list(anthill_t *anthill)
{
    if (anthill == NULL || anthill->rooms.rooms == NULL
        || anthill->tunnels.tunnels == NULL || anthill->ants == 0)
        return;
    for (size_t i = 0; i < anthill->tunnels.count; i++)
        add_tunnel(anthill, anthill->tunnels.tunnels + i);
}

room_t *get_graph(anthill_t *anthill)
{
    for (size_t i = 0; i < anthill->rooms.count; i++)
        if (anthill->rooms.rooms[i].type == ROOM_ENTRANCE)
            return anthill->rooms.rooms + i;
    return NULL;
}
