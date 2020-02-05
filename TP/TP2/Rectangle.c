#include <ncurses.h>

void rectangle(int x1, int y1, int x2, int y2, int color) {
    attron(COLOR_PAIR(color));
    mvhline(y1, x1, 0, x2 - x1);
    mvhline(y2, x1, 0, x2 - x1);
    mvvline(y1, x1, 0, y2 - y1);
    mvvline(y1, x2, 0, y2 - y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
    attroff(COLOR_PAIR(color));
}

int main(void) {
    initscr();
    start_color();
    curs_set(0);

    init_pair(1, COLOR_RED, COLOR_BLACK);
    rectangle(COLS / 2 - 7, LINES / 2 - 1, COLS / 2 + 7, LINES / 2 + 1, 1);

    getch();
    endwin();
    return 0;
}