/*
** EPITECH PROJECT, 2023
** lemin
** File description:
** linked
*/

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
    size_t new_size = (from->leaves.n) ? from->leaves.n + 1 : 2;

    if (from == NULL || to == NULL)
        return;
    my_reallocarray(
        from->leaves.arr, new_size,
        from->leaves.n, sizeof(room_t *)
    );
    from->leaves.arr[from->leaves.n] = to;
    from->leaves.arr[from->leaves.n + 1] = NULL;
    from->leaves.n = new_size;
}

void create_linked_list(anthill_t *anthill)
{
    if (anthill == NULL || anthill->rooms.rooms == NULL
        || anthill->tunnels.tunnels == NULL || anthill->ants != 0)
        return;
    for (size_t i = 0; i < anthill->tunnels.count; i++)
        add_tunnel(anthill, anthill->tunnels.tunnels + i);
}
