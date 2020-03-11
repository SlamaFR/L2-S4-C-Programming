#include "Direction.h"

int allowed_direction(Direction direction1, Direction direction2) {
    if (direction1 == SOUTH && direction2 == NORTH)
        return 0;
    if (direction1 == NORTH && direction2 == SOUTH)
        return 0;
    if (direction1 == EAST && direction2 == WEST)
        return 0;
    if (direction1 == WEST && direction2 == EAST)
        return 0;
    return 1;
}
