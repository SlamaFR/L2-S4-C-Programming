#include <ncurses.h>

int main(void) {
    initscr();
    attron(A_BOLD | A_UNDERLINE);

    printw("*10*");

    refresh();
    getch();

    endwin();
    return 0;
}
