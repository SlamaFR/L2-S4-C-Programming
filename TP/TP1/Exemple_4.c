#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void dessiner_chat(int y, int x) {
    mvprintw(y, x, "*****");
    mvaddch(y + 1, x, '*');
    mvaddch(y + 1, x + 2, '*');
    mvaddch(y + 1, x + 4, '*');
    mvprintw(y + 2, x, "*****");
}

void effacer_chat(int y, int x) {
    mvprintw(y, x, "     ");
    mvprintw(y + 1, x, "     ");
    mvprintw(y + 2, x, "     ");
}

void afficher_texte_centre(char *str) {
    unsigned long taille = strlen(str);
    mvprintw(LINES / 2, COLS / 2 - taille / 2, str);
}

int main() {
    int touche;
    int chat_x, chat_y;
    int souris_x, souris_y;
    MEVENT ev;

    srand(time(NULL));

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    chat_x = rand() % (COLS - 4);
    chat_y = rand() % (LINES - 2);
    while (1) {
        touche = getch();
        if (touche == KEY_MOUSE && getmouse(&ev) == OK) {
            souris_x = ev.x;
            souris_y = ev.y;
            if ((chat_x <= souris_x) && (souris_x <= chat_x + 4)
                && (chat_y <= souris_y) && (souris_y <= chat_y + 2)) {
                effacer_chat(chat_y, chat_x);

                if ((souris_x - chat_x == 1 || souris_x - chat_x == 3)
                    && souris_y - chat_y == 1) {
                    mvaddch(souris_y, souris_x, 'X');
                    continue;
                }
                afficher_texte_centre("Attrape !");

                refresh();
                clear();
                usleep(1500000);

                chat_x = rand() % (COLS - 4);
                chat_y = rand() % (LINES - 2);
            }
        }
        dessiner_chat(chat_y, chat_x);
        refresh();
    }

    getch();
    endwin();
    return 0;
}