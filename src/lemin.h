/*
** EPITECH PROJECT, 2023
** lemin
** File description:
** lemin
*/

#ifndef LEMIN_H_
    #define LEMIN_H_

    #include <stdbool.h>
    #include <stddef.h>

enum steps_e {
    ST_ANTS_NUM,
    ST_ROOMS,
    ST_ROOM_ENTRANCE,
    ST_ROOM_EXIT,
    ST_TUNNELS,
};

enum room_type_e {
    ROOM_NORMAL,
    ROOM_ENTRANCE,
    ROOM_EXIT,
};

typedef struct room_s {
    char *name;
    size_t x;
    size_t y;
    enum room_type_e type;
    bool visited;
    struct {
        size_t n;
        struct room_s **arr;
    } leaves;
} room_t;

typedef struct {
    room_t *rooms;
    size_t count;
    size_t allocated;
    bool has_entrance;
    bool has_exit;
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
void parse_me_baby(anthill_t *anthill);
void create_linked_list(anthill_t *anthill);
void free_ants(anthill_t *anthill);
room_t *get_graph(anthill_t *anthill);
void move_ants(room_t *graph, anthill_t *anthill);

#endif
