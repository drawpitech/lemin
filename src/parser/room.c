/*
** EPITECH PROJECT, 2023
** lemin
** File description:
** room
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "my/io.h"
#include "my/debug.h"
#include "my/std.h"
#include "my/string.h"

#include "lemin.h"
#include "parser.h"

static
void resize_anthill(anthill_rooms_t *rooms)
{
    size_t new_size;

    if (rooms->allocated > rooms->count + 1)
        return;
    new_size = (rooms->allocated) ? rooms->allocated * 2 : 16;
    rooms->rooms = my_reallocarray(
        rooms->rooms, new_size, rooms->allocated, sizeof(*rooms->rooms)
    );
    rooms->allocated = new_size;
}

static
room_t *get_room_data(char *line)
{
    static room_t room;
    char *dup = my_strdup(line);
    char *ptr_x = my_strfind(dup, ' ');
    char *ptr_y = (ptr_x == NULL) ? NULL : my_strfind(ptr_x + 1, ' ');

    if (ptr_x == NULL || ptr_y == NULL || dup == NULL)
        return NULL;
    *ptr_x = '\0';
    *ptr_y = '\0';
    room.name = dup;
    room.x = str_to_int(ptr_x + 1);
    room.y = str_to_int(ptr_y + 1);
    if (room.x == INT64_MAX || room.y == INT64_MAX)
        return NULL;
    return &room;
}

int get_room(char *line, anthill_t *anthill)
{
    room_t *room = NULL;

    room = get_room_data(line);
    if (room == NULL)
        return RET_ERROR;
    resize_anthill(&anthill->rooms);
    anthill->rooms.rooms[anthill->rooms.count] = *room;
    anthill->rooms.count += 1;
    DEBUG("%s %d %d", room->name, room->x, room->y);
    return RET_VALID;
}
