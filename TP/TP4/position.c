#include <ncurses.h>
#include "tablet.h"
#include "player.h"
#include "position.h"

int isGameOver(Position position, Player *winner) {
    if (!position.tablet.tab[0][0]) {
        *winner = position.player;
        return 1;
    }
    return 0;
}

void displayPosition(Position position, int matchIndex, int matchAmount) {
    int i, j, width, height;
    clear();

    attron(A_REVERSE);
    mvprintw((LINES - CELL_SIZE * N - N) / 2, COLS / 2 - 13, " -=*   C H O M P   *=- ");
    attroff(A_REVERSE);
    mvprintw(1, 2, "Match %d / %d", matchIndex, matchAmount);
    attron(A_BOLD);
    if (position.player == PLAYER_1)
        mvprintw((LINES - CELL_SIZE * N) / 2, COLS / 2 - 7, "> Joueur 1 <");
    else
        mvprintw((LINES - CELL_SIZE * N) / 2, COLS / 2 - 7, "> Joueur 2 <");
    attroff(A_BOLD);

    if (!position.tablet.tab[0][1] && !position.tablet.tab[1][0])
        mvprintw((LINES - CELL_SIZE * N) / 2 + 1, COLS / 2 - 11, "Accepte ta défaite !");

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            attron(COLOR_PAIR(position.tablet.tab[i][j]));
            for (height = 0; height < CELL_SIZE / 2; height++) {
                for (width = 0; width < CELL_SIZE; width++) {
                    mvprintw((LINES - (CELL_SIZE / 2 + 1) * N) / 2 + 1 + i * CELL_SIZE / 2 + height + i,
                             (COLS - (CELL_SIZE + 2) * M) / 2 + j * CELL_SIZE + width + 2 * j, " ");
                }
            }
            attroff(COLOR_PAIR(position.tablet.tab[i][j]));
        }
    }
    refresh();
}
