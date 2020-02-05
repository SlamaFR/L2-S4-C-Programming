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

void rectangle2(int x1, int y1, int x2, int y2, int color) {
    int i, j;
    attron(COLOR_PAIR(color));
    for (i = 0; i < y2 - y1; i++) {
        for (j = 0; j < x2 - x1; j++) {
            mvaddch(y1 + i, x1 + j, ' ');
        }
    }
    attroff(COLOR_PAIR(color));
}

int main(void) {
    int touche, color = 1;
    MEVENT ev;

    initscr();
    cbreak();
    noecho();
    start_color();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_BLUE, COLOR_BLUE);

    rectangle(COLS / 2 - 3, LINES / 2 - 3, COLS / 2 + 3, LINES / 2 + 3, color);

    while (1) {
        touche = getch();
        if (touche == KEY_MOUSE && getmouse(&ev) == OK) {
            if (ev.x >= COLS / 2 - 3 && ev.x <= COLS / 2 + 3 &&
                ev.y >= LINES / 2 - 3 && ev.y <= LINES / 2 + 3) {
                color = color == 1 ? 2 : 1;
                rectangle(COLS / 2 - 3, LINES / 2 - 3, COLS / 2 + 3, LINES / 2 + 3, color);
            }
        }
        refresh();
    }
    getch();
    endwin();
    return 0;
}