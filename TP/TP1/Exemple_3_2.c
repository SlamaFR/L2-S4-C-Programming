#include <ncurses.h>
#include <math.h>

int main() {
    int touche;
    int x, y;
    int x_prec, y_prec;
    int step = 1;
    double log, log_prec;

    initscr();
    noecho();
    curs_set(0);

    x = COLS / 2;
    y = LINES / 2;
    log = log10(step);
    mvaddch(y, x, 'o');

    while (1) {
        mvprintw(LINES - 1, 0, "Pas : %d", step);
        x_prec = x;
        y_prec = y;
        log_prec = log;

        touche = getch();
        if (touche == 'q' && x - step >= 0)
            x -= step;
        if (touche == 'd' && x + step <= COLS - 1)
            x += step;
        if (touche == 'z' && y - step >= 0)
            y -= step;
        if (touche == 's' && y + step <= LINES - 1)
            y += step;
        if (touche == 'i') {
            x = COLS / 2;
            y = LINES / 2;
        }
        if (touche == 'p')
            step++;
        if (touche == 'm')
            step--;

        log = log10(step);

        mvaddch(y_prec, x_prec, ' ');
        mvaddch(y, x, 'o');
        mvprintw(LINES - 1, 0, "Pas : %d", step);

        if (log != log_prec)
            delch();

        refresh();
    }
    getch();
    endwin();
    return 0;
}