/*
** EPITECH PROJECT, 2023
** lemin
** File description:
** parser
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

static
int get_command(char *line, anthill_t *anthill)
{
    if (line[1] != '#')
        return RET_VALID;
    if (my_strcmp(line, "##start")) {
        DEBUG_MSG("ENTRANCE");
        anthill->step = ST_ROOM_ENTRANCE;
        return RET_VALID;
    }
    if (my_strcmp(line, "##end")) {
        DEBUG_MSG("EXIT");
        anthill->step = ST_ROOM_EXIT;
        return RET_VALID;
    }
    return RET_ERROR;
}

static
int get_ants_num(char *line, anthill_t *anthill)
{
    long value = str_to_int(line);

    if (value == INT64_MAX)
        return RET_ERROR;
    anthill->ants = value;
    anthill->step = ST_ROOMS;
    DEBUG("%d ants.", value);
    return RET_VALID;
}

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
int get_room(char *line, anthill_t *anthill)
{
    char *dup = my_strdup(line);
    char *ptr_x = my_strfind(dup, ' ');
    char *ptr_y = (ptr_x == NULL) ? NULL : my_strfind(ptr_x + 1, ' ');
    room_t *room = NULL;

    if (ptr_x == NULL || ptr_y == NULL || dup == NULL)
        return RET_ERROR;
    resize_anthill(&anthill->rooms);
    room = anthill->rooms.rooms + anthill->rooms.count;
    anthill->rooms.count += 1;
    room->name = dup;
    *ptr_x = '\0';
    *ptr_y = '\0';
    room->x = str_to_int(ptr_x + 1);
    room->y = str_to_int(ptr_y + 1);
    DEBUG("ROOM: `%s`, x: %d, y: %d", room->name, room->x, room->y);
    if (room->x == INT64_MAX || room->y == INT64_MAX)
        return RET_ERROR;
    return RET_VALID;
}

int process_line(char *line, anthill_t *anthill)
{
    if (line[0] == '#')
        return get_command(line, anthill);
    if (anthill->step == ST_ANTS_NUM)
        return get_ants_num(line, anthill);
    if (my_strfind(line, '-') == NULL)
        return get_room(line, anthill);
    return RET_VALID;
}
