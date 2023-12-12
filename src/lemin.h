/*
** EPITECH PROJECT, 2023
** lemin
** File description:
** lemin
*/

#ifndef LEMIN_H_
    #define LEMIN_H_

    #include <stddef.h>

enum steps_e {
    ST_ANTS_NUM,
    ST_ROOMS,
    ST_ROOM_ENTRANCE,
    ST_ROOM_EXIT,
    ST_TUNNELS,
};

typedef struct {
    char *name;
    size_t x;
    size_t y;
} room_t;

typedef struct {
    room_t *rooms;
    size_t count;
    size_t allocated;
} anthill_rooms_t;

typedef struct {
    char *from;
    char *to;
} tunnel_t;

typedef struct {
    tunnel_t *tunnels;
    size_t count;
    size_t allocated;
} anthill_tunnels_t;

typedef struct anthill_s {
    size_t ants;
    char step;
    anthill_rooms_t rooms;
    anthill_tunnels_t tunnels;
} anthill_t;

int lemin(void);
int process_line(char *line, anthill_t *anthill);

#endif
