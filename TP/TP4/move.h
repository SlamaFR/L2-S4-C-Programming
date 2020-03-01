#include "position.h"

#ifndef CHOMP_MOVE_H
#define CHOMP_MOVE_H

typedef struct s_move {
    int x, y;
} Move;

int isLegal(Position position, Move move);
void play(Position *position, Move move);
Move readMove(Position position);

#endif
