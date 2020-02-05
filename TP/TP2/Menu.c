#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

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

void credit() {
    nodelay(stdscr, FALSE);
    clear();
    attron(A_BOLD);
    mvprintw(LINES / 2 - 1, COLS / 2 - 10, "Programme créé par :");
    attroff(A_BOLD);
    mvprintw(LINES / 2 + 1, COLS / 2 - 5, "Irwin MADET");
    mvprintw(LINES / 2 + 2, COLS / 2 - 8, "Chayma GUERRASSI");
    refresh();
    getch();
    nodelay(stdscr, TRUE);
}

void options(int *speed) {
    char input[10];

    echo();
    curs_set(1);
    nodelay(stdscr, FALSE);

    clear();
    attron(A_BOLD);
    mvprintw(LINES / 2 - 1, COLS / 2 - 3, "OPTIONS");
    attroff(A_BOLD);

    mvprintw(LINES / 2 + 2, COLS / 2 - 10, "Vitesse actuelle = %d", *speed);
    mvprintw(LINES / 2 + 1, COLS / 2 - 13, "Vitesse de deplacement : ");
    refresh();

    getstr(input);
    *speed = atoi(input);

    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
}

void game(int speed) {
    int key, x, y, xv = 1, yv = 1;
    int moving = 0, running = 1;

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
            usleep(1000000 / speed);
        }
        refresh();
    }
}

void menu() {
    char *choices[] = {"Demarrer", "Options", "Credits", "Quitter"};
    int key, choice = 0, i, x, y, velocity = 2;

    while (1) {
        key = getch();

        clear();
        for (i = 0; i < 4; i++) {
            x = (COLS - (int) strlen(choices[i])) / 2 - 1;
            y = LINES / 2 - 4 + i * 2;

            if (i == choice) attron(A_REVERSE);
            mvprintw(y, x, "%d - %s", i + 1, choices[i]);
            if (i == choice) attroff(A_REVERSE);
        }

        if (key != ERR) {
            if (key == KEY_UP) {
                if (choice > 0) choice--;
                else choice = 3;
            }
            if (key == KEY_DOWN) {
                if (choice < 3) choice++;
                else choice = 0;
            }
            if (key == '\n') {
                switch (choice) {
                    case 0:
                        game(velocity);
                        return;
                    case 1:
                        options(&velocity);
                        break;
                    case 2:
                        credit();
                        break;
                    case 3:
                        return;
                }
            }
        }
        refresh();
    }
}

int main(void) {
    initscr();
    cbreak();
    noecho();
    start_color();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    init_pair(0, COLOR_WHITE, COLOR_BLACK);

    menu();
    endwin();
    return 0;
}