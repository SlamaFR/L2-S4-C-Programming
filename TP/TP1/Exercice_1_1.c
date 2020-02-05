#include <ncurses.h>

void method1() {
    move(4, 8);
    addch('4');
    addch('!');
    addch('+');
    addch('2');
    addch('!');
    refresh();
}

void method2() {
    mvaddch(4, 8, '4');
    mvaddch(4, 9, '!');
    mvaddch(4, 10, '+');
    mvaddch(4, 11, '2');
    mvaddch(4, 12, '!');
    refresh();
}

void method3() {
    mvprintw(4, 8, "4!+2!");
    refresh();
}

int main(void) {
    initscr();

    method1();
    getch();

    clear();
    method2();
    getch();

    clear();
    method3();
    getch();

    endwin();
    return 0;
}
