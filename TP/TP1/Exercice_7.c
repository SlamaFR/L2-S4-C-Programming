#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int key, running = 1, delay = 1000000, x, y;
    initscr();
    curs_set(0);
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    cbreak();

    srand(time(NULL));

    x = COLS / 2;
    y = LINES / 2;

    mvaddch(y, x, 'o');
    while (1) {
        key = getch();

        if (key != ERR) {
            if (key == '\n')
                running = !running;

            if (key == KEY_UP)
                delay /= 2;
            if (key == KEY_DOWN)
                delay *= 2;
        }

        if (!running)
            continue;

        mvaddch(y, x, 'x');
        if (rand() % 2) {
            // Déplacement vertical.
            y += (rand() % 2) ? 1 : -1;
        } else {
            // Déplacement horizontal.
            x += (rand() % 2) ? 1 : -1;
        }

        if (x < 0) {
            x++;
            continue;
        }
        if (x > COLS - 1) {
            x--;
            continue;
        }if (y < 0) {
            y++;
            continue;
        }
        if (y > LINES - 1) {
            y--;
            continue;
        }

        mvaddch(y, x, 'o');
        refresh();
        usleep(delay);
    }

    endwin();
    return 0;
}