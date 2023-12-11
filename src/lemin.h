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
    size_t ants;
    char step;
    anthill_rooms_t rooms;
} anthill_t;

int lemin(void);
int process_line(char *line, anthill_t *anthill);

#endif
