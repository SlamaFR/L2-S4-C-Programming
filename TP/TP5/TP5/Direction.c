//
//  Direction.c
//  TP5
//

#include "Direction.h"
#include "Serpent.h"

int direction_autorisee(Direction direction, Serpent serpent){
    
    if (direction == SUD && serpent.direction == NORD)
        return 0;
    if (direction == NORD && serpent.direction == SUD)
        return 0;
    if (direction == EST && serpent.direction == OUEST)
        return 0;
    if (direction == OUEST && serpent.direction == EST)
        return 0;
    
    return 1;
}

