#include <ncurses.h>

int main(void) {
    char chaine[128];

    initscr();

    mvgetstr(4, 2, chaine);
    mvprintw(0, 0, chaine);

    refresh();
    getch();


    endwin();
    return 0;
}