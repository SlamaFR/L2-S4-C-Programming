#ifndef __DIRECTION_H
#define __DIRECTION_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST
} Direction;

int allowed_direction(Direction direction1, Direction direction2);

#endif /* __DIRECTION_H */
