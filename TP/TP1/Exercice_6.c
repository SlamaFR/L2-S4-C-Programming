#include <ncurses.h>

int main(void) {
    int size, i, j;
    initscr();

    scanw("%d", &size);

    for (i = 0; i < size + 1; i++) {
        move(i, 0);
        for (j = 0; j < i; j++) {
            addch('*');
        }
    }

    getch();
    endwin();
    return 0;
}