#include <assert.h>
#include <ncurses.h>
#include "tablet.h"

Tablet createTablet() {
    Tablet tablet;
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            tablet.tab[i][j] = 1;
    return tablet;
}

void eat(Tablet *tablet, int x, int y) {
    int i, j;
    assert(x < COLS);
    assert(y < LINES);
    assert(tablet != NULL);

    for (i = y; i < N; i++)
        for (j = x; j < M; j++)
            tablet->tab[i][j] = 0;
}
