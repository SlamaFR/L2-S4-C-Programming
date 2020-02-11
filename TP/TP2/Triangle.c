/* Chayma Guerrasi */

#include <stdlib.h>
#include <ncurses.h>
#include <assert.h>

/**
 * Fonction qui dessine un triangle de caractère c,
 * de base 2n+1 et de hauteur n+1 pointant vers le bas.
 */
void triangle(int n, char c) {
    int i, j;
    for (i = 0; i < n + 1; i++) {
        move((LINES - n) / 2 + i, COLS / 2 - n);
        for (j = 0; j < 2 * n + 1; j++)
            printw("%c", j < i || j >= (2 * n + 1 - i) ? ' ' : c);
    }
}


int main(int argc, char *argv[]) {
    int n;
    char c;
    assert(argc >= 3);

    /* Récupération des arguments. */
    n = atoi(argv[1]);
    c = *argv[2];

    initscr();
    curs_set(0);
    noecho();

    triangle(n, c);

    getch();
    endwin();
    return 0;
}

