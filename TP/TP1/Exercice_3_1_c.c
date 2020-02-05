#include <ncurses.h>

int main(void) {
    int i = 1, x = 0, y = 0;

    initscr();

    while (i) {
        mvscanw(y, x, "%d", &i);
        x++;
        y++;
    }

    endwin();
    return 0;
}