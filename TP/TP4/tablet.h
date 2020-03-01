#ifndef CHOMP_TABLET_H
#define CHOMP_TABLET_H

#define N 8
#define M 16
#define CELL_SIZE 4

typedef struct s_tablet {
    int tab[N][M];
} Tablet;

Tablet createTablet();
void eat(Tablet *tablet, int x, int y);

#endif
