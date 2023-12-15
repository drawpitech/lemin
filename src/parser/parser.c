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

#include "parser.h"

static
int get_command(char *line, anthill_t *anthill)
{
    if (line[1] != '#')
        return RET_VALID;
    if (my_strcmp(line, "##start") == 0) {
        DEBUG_MSG("ENTRANCE ROOM");
        anthill->step = ST_ROOM_ENTRANCE;
        return RET_VALID;
    }
    if (my_strcmp(line, "##end") == 0) {
        DEBUG_MSG("EXIT ROOM");
        anthill->step = ST_ROOM_EXIT;
        return RET_VALID;
    }
    return RET_VALID;
}

static
int get_ants_num(char *line, anthill_t *anthill)
{
    long value = my_strtol(line, NULL);

    if (value == INT64_MAX)
        return RET_ERROR;
    anthill->ants = value;
    anthill->step = ST_ROOMS;
    DEBUG("%d ants.", value);
    return RET_VALID;
}

static
void resize_anthill(anthill_tunnels_t *tunnels)
{
    size_t new_size;

    if (tunnels->allocated > tunnels->count + 1)
        return;
    new_size = (tunnels->allocated) ? tunnels->allocated * 2 : 16;
    tunnels->tunnels = my_reallocarray(
        tunnels->tunnels, new_size,
        tunnels->allocated, sizeof(*tunnels->tunnels)
    );
    tunnels->allocated = new_size;
}

static
int get_tunnel(char *line, anthill_t *anthill)
{
    char *dup = my_strdup(line);
    char *ptr = my_strchr(dup, '-');

    resize_anthill(&anthill->tunnels);
    anthill->tunnels.tunnels[anthill->tunnels.count] = (tunnel_t){
        .from = dup,
        .to = ptr + 1,
    };
    *ptr = '\0';
    anthill->tunnels.count += 1;
    return RET_VALID;
}

static
int process_line(char *line, anthill_t *anthill)
{
    if (line[0] == '#')
        return get_command(line, anthill);
    if (anthill->step == ST_ANTS_NUM)
        return get_ants_num(line, anthill);
    if (my_strchr(line, '-') == NULL)
        return get_room(line, anthill);
    return get_tunnel(line, anthill);
}

static
void sanitize(char *line)
{
    char *tmp = my_strchr(line, '\n');

    if (tmp == NULL)
        return;
    *tmp = '\0';
}

void parse_me_baby(anthill_t *anthill)
{
    size_t size = 0;
    char *buffer = NULL;

    while (getline(&buffer, &size, stdin) != -1) {
        sanitize(buffer);
        DEBUG("-> [%s]", buffer);
        if (buffer[0] == '\0' || process_line(buffer, anthill) == RET_ERROR)
            break;
    }
    if (buffer != NULL)
        free(buffer);
}
