#ifndef __SERPENT_H
#define __SERPENT_H

#include <stdio.h>
#include <stdlib.h>
#include "Direction.h"
#include "Case.h"

/* Déclaration de liste chainée représentant le serpent */
typedef struct __s_snakeCell {
    Cell snake_cell;
    struct __s_snakeCell *next;
} SnakeCell, *SnakeList;


typedef struct __s_snake {
    Direction direction;
    SnakeList body;
} Snake;

int insert_head(SnakeList *list, Cell cell);

void remove_tail(SnakeList *list);

#endif /* __SERPENT_H */
