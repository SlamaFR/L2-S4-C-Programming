#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void rectangle(int x1, int y1, int x2, int y2, int color) {
    int i, j;
    attron(COLOR_PAIR(color));
    for (i = y1; i <= y2 && i < LINES; i++) {
        for (j = x1; j <= x2 && j < COLS; j++) {
            mvaddch(i, j, ' ');
        }
    }
    attroff(COLOR_PAIR(color));
}

void credit() {
    clear();
    attron(A_BOLD);
    mvprintw(LINES / 2 - 3, COLS / 2 - 10, "Programme créé par :");
    attroff(A_BOLD);
    mvprintw(LINES / 2 - 2, COLS / 2 - 5, "Irwin MADET");
    mvprintw(LINES / 2 - 1, COLS / 2 - 8, "Chayma GUERRASSI");


    attron(A_BOLD);
    mvprintw(LINES / 2 + 1, COLS / 2 - 5, "Affilié à :");
    attroff(A_BOLD);
    mvprintw(LINES / 2 + 2, COLS / 2 - 12, "Université Gustave Eiffel");

    mvprintw(LINES / 2 + 4, COLS / 2 - 13, "Date d'édition : 11/02/2020");
    refresh();
    getch();
}

void options(int *speed) {
    char input[10];

    echo();
    curs_set(1);

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
}

void game(int speed) {
    nodelay(stdscr, TRUE);
    int key, x, y, xv = 1, yv = -1;
    int moving = 0, running = 1;

    x = COLS / 2 - 2;
    y = LINES / 2 - 2;

    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_BLUE, COLOR_BLUE);

    rectangle(0, 0, COLS, LINES, 1);
    rectangle(x, y, x + 1, y, 2);

    while (running) {
        key = getch();

        if (key != ERR) {
            if (key == '\n') {
                if (!moving) moving = 1;
                else running = 0;
            }
        }

        if (moving) {

            if (x + xv < 0 || x + xv > COLS - 2)
                xv = -xv;
            if (y + yv < 0 || y + yv > LINES - 1)
                yv = -yv;

            rectangle(x, y, x + 1, y, 1);
            x += xv;
            y += yv;
            rectangle(x, y, x + 1, y, 2);
            usleep(1000000 / speed);
        }
        refresh();
    }
}

void menu() {
    char *choices[] = {"Demarrer", "Options", "Credits", "Quitter"};
    int key = ERR, choice = 0, i, x, y, velocity = 2;

    while (1) {
        clear();
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
                default:
                    return;
            }
            clear();
        }
        for (i = 0; i < 4; i++) {
            x = (COLS - (int) strlen(choices[i])) / 2 - 1;
            y = LINES / 2 - 4 + i * 2;

            if (i == choice) attron(A_REVERSE);
            mvprintw(y, x, "%d - %s", i + 1, choices[i]);
            if (i == choice) attroff(A_REVERSE);
        }
        refresh();
        key = getch();
    }
}

int main(void) {
    initscr();
    cbreak();
    noecho();
    start_color();
    keypad(stdscr, TRUE);
    //keypad(stdscr, TRUE);
    curs_set(0);

    init_pair(0, COLOR_WHITE, COLOR_BLACK);

    menu();
    endwin();
    return 0;
}