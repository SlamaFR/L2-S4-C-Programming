#include <ncurses.h>
#include <assert.h>
#include "position.h"
#include "move.h"
#include "tablet.h"

int isLegal(Position position, Move move) {
    assert(move.x >= 0);
    assert(move.y >= 0);
    assert(move.x < M);
    assert(move.y < N);

    return position.tablet.tab[move.y][move.x];
}

void play(Position *position, Move move) {
    assert(position != NULL);

    eat(&position->tablet, move.x, move.y);
    position->player = adversary(position->player);
}

Move readMove(Position position) {
    int c;
    MEVENT ev;
    Move move;

    do {
        c = getch();

        if (c == KEY_MOUSE && getmouse(&ev) == OK) {
            move.x = (ev.x - ((COLS - (CELL_SIZE + 2) * M) / 2)) / (CELL_SIZE + 2);
            move.y = (ev.y - ((LINES - (CELL_SIZE / 2 + 1) * N) / 2)) / (CELL_SIZE / 2 + 1);

        } else continue;
    } while (move.x >= M || move.y >= N || !isLegal(position, move) || mvinch(ev.y, ev.x) == ' ');

    return move;
}
