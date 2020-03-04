//
//  Direction.h
//  TP5
//

#ifndef Direction_h
#define Direction_h

#include <stdio.h>
#include <stdlib.h>

typedef enum{
    NORD,
    SUD,
    EST,
    OUEST

}Direction;

int direction_autorisee(Direction direction, Serpent serpent);


#endif /* Direction_h */
