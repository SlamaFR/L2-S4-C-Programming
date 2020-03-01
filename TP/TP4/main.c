#include <ncurses.h>
#include <unistd.h>
#include "tablet.h"
#include "player.h"
#include "position.h"
#include "move.h"

int main(void) {
    Position position;
    Player winner;
    Move move;
    int scorePlayer1 = 0, scorePlayer2 = 0;
    int matchPlayer1, matchPlayer2, matches, i;

    initscr();
    curs_set(0);
    start_color();
    init_pair(0, COLOR_WHITE, COLOR_WHITE);
    init_pair(1, COLOR_YELLOW, COLOR_YELLOW);
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    mvprintw(LINES / 2 - 2, COLS / 2 - 24, "Joueur 1, combien de matchs voulez-vous jouer ? ");
    scanw("%d", &matchPlayer1);
    mvprintw(LINES / 2, COLS / 2 - 24, "Joueur 2, combien de matchs voulez-vous jouer ? ");
    scanw("%d", &matchPlayer2);
    matches = (matchPlayer1 + matchPlayer2) / 2;
    noecho();

    attron(A_BOLD);
    mvprintw(LINES / 2 + 3, COLS / 2 - 13, "Vous jouerez %2d match(s) !", matches);
    attroff(A_BOLD);
    refresh();
    usleep(2500000);

    if (matches == 0)
        return 1;



    for (i = 0; i < matches; i++) {
        position.tablet = createTablet();
        position.player = PLAYER_1;
        while (!isGameOver(position, &winner)) {
            displayPosition(position, i + 1, matches);
            move = readMove(position);
            play(&position, move);
        }
        winner == PLAYER_1 ? scorePlayer1++ : scorePlayer2++;
    }

    clear();
    if (scorePlayer1 > scorePlayer2) {
        mvprintw(LINES / 2, COLS / 2 - 16, "Le Joueur 1 remporte la partie !");
    } else if (scorePlayer1 < scorePlayer2) {
        mvprintw(LINES / 2, COLS / 2 - 16, "Le Joueur 2 remporte la partie !");
    } else {
        mvprintw(LINES / 2, COLS / 2 - 16, "Egalité entre les deux joueurs !");
    }
    refresh();
    getch();

    endwin();
    return 0;
}
