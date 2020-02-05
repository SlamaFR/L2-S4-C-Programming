#include <ncurses.h>

int main(void) {
    int i, j;
    initscr();

    start_color();
    curs_set(0);

    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);

    for (i = 0; i < 10; i++) {
        move(LINES / 2 - i, COLS / 2);
        for (j = i; j < i + 10; j++) {
            attron(j % 2 == 0 ? COLOR_PAIR(1) : COLOR_PAIR(2));
            addch(' ');
            attroff(j % 2 == 0 ? COLOR_PAIR(1) : COLOR_PAIR(2));
        }
    }

    getch();
    endwin();
    return 0;
}