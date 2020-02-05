#include <ncurses.h>

int main() {
    initscr();

    start_color();
    init_pair(1, COLOR_RED, COLOR_CYAN);
    init_pair(2, COLOR_GREEN, COLOR_BLUE);

    curs_set(0);

    attron(COLOR_PAIR(1));
    mvprintw(2, 3, "Abc123 **  *");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    mvprintw(2, 16, "2121");
    attroff(COLOR_PAIR(2));

    refresh();
    getch();
    endwin();
    return 0;
}