#include <ncurses.h>

int main() {
    char chaine[128];
    int entier;

    initscr();

    getstr(chaine);
    mvprintw(3, 0, "Chaine lue : %s", chaine);

    mvscanw(10, 0, "%d", &entier);

    mvprintw(11, 0, "Entier lue : %d", entier);

    refresh();
    getch();
    endwin();
    return 0;
}