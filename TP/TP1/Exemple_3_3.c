#include <ncurses.h>
#include <unistd.h>

int main() {
    int touche, val, delai;

    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    cbreak();

    val = 0;
    delai = 1000000;
    mvprintw(0, 0, "Valeur : %3d", val);
    while (1) {
        touche = getch();
        if (touche != ERR) {
            if (touche == 'r')
                val = 0;
            if (touche == 'b')
                delai /= 2;
            if (touche == 't')
                delai *= 2;
            if (touche == 'q')
                break;
        }
        mvprintw(0, 0, "Valeur : ");
        attron(A_BOLD);
        printw("%3d", val);
        attroff(A_BOLD);
        refresh();

        val = (val + 1) % 128;
        usleep(delai);
    }
    getch();
    endwin();
    return 0;
}