#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main() {
    int touche, chiffre, x, y;
    int souris_x, souris_y;
    MEVENT ev;

    srand(time(NULL));

    initscr();
    cbreak();
    noecho();
    start_color();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    init_pair(1, COLOR_BLUE, COLOR_BLUE);

    for (y = 0; y < LINES; y++) {
        for (x = 0; x < COLS; x++) {
            mvaddch(y, x, '0');
        }
    }

    while (1) {
        touche = getch();
        if (touche == KEY_MOUSE && getmouse(&ev) == OK) {
            chiffre = mvinch(ev.y, ev.x);

            if (chiffre >= 48 && chiffre < 57) {
                mvaddch(ev.y, ev.x, ++chiffre);
            } else if (chiffre == 57) {
                attron(COLOR_PAIR(1));
                mvaddch(ev.y, ev.x, ' ');
                attroff(COLOR_PAIR(1));
            }
        }
        refresh();
    }
    getch();
    endwin();
    return 0;
}