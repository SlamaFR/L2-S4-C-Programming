#include <ncurses.h>
#include <unistd.h>

void rectangle(int x1, int y1, int x2, int y2, int color) {
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
    int key, x, y, xv = 2, yv = 2;
    int moving = 0, running = 1;

    initscr();
    cbreak();
    noecho();
    start_color();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    x = COLS / 2 - 2;
    y = LINES / 2 - 2;

    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_BLUE, COLOR_BLUE);

    rectangle(0, 0, COLS, LINES, 1);
    rectangle(x, y, x + 2, y + 2, 2);

    while (running) {
        key = getch();

        if (key != ERR) {
            if (key == '\n') {
                if (!moving) moving = 1;
                else running = 0;
            }
        }

        if (moving) {

            if (x + xv < 0 || x + xv > COLS - 1)
                xv = -xv;
            if (y + yv < 0 || y + yv > LINES - 1)
                yv = -yv;

            rectangle(x, y, x + 2, y + 2, 1);
            x += xv;
            y += yv;
            rectangle(x, y, x + 2, y + 2, 2);
            usleep(1000000);
        }
        refresh();
    }
    endwin();
    return 0;
}