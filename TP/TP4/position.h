#include "tablet.h"
#include "player.h"

#ifndef POSITION_POSITION_H
#define POSITION_POSITION_H

typedef struct s_position {
    Tablet tablet;
    Player player;
} Position;

int isGameOver(Position position, Player *winner);
void displayPosition(Position position, int matchIndex, int matchAmount);

#endif
