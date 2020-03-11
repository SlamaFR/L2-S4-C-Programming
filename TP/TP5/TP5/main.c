#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include "Monde.h"

#define APPLE_COLOR 1
#define SNAKE_BODY 2
#define SNAKE_HEAD 3

#define NDET

void display_grid(World world) {
    int i, j;
    for (i = 0; i < world.height; i++) {
        for (j = 0; j < world.width; j++) {
            mvprintw(i * 2, j * 4, "+---");
        }
        printw("+");
        for (j = 0; j < world.width; j++) {
            mvprintw(i * 2 + 1, j * 4, "|   ");
        }
        printw("|");
    }
    for (j = 0; j < world.width; j++) {
        mvprintw(i * 2, j * 4, "+---");
    }
    printw("+");
}

void display_apple(Apple apple) {
    int x = apple.apple_cell.x, y = apple.apple_cell.y;
    attron(COLOR_PAIR(APPLE_COLOR));
    mvprintw(2 * y + 1, 4 * x + 2, "X");
    attroff(COLOR_PAIR(APPLE_COLOR));
}

void display_snake(Snake snake) {
    SnakeList lst;
    int i = 0, x, y;
    for (lst = snake.body; lst; lst = lst->next) {
        x = lst->snake_cell.x;
        y = lst->snake_cell.y;
        if (i) {
            attron(COLOR_PAIR(SNAKE_BODY) | A_BOLD);
            mvprintw(2 * y + 1, 4 * x + 2, "o");
            attroff(COLOR_PAIR(SNAKE_BODY) | A_BOLD);
        } else {
            attron(COLOR_PAIR(SNAKE_HEAD) | A_BOLD);
            mvprintw(2 * y + 1, 4 * x + 2, "O");
            attroff(COLOR_PAIR(SNAKE_HEAD) | A_BOLD);
        }
        i++;
    }
}

void display_world(World world) {
    AppleList apples;
    display_grid(world);
    display_snake(world.snake);
    if (world.apples != NULL)
        for (apples = world.apples; apples; apples = apples->next)
            display_apple(apples->apple);

    mvprintw(world.height * 2 + 3, 5, "Pommes mangees : %d", world.eaten_apple_amount);
}

int main(int ac, char **av) {
    World world;
    int running = 1, paused = 0, key;
    initscr();
    noecho();
    curs_set(0);
    start_color();

    init_pair(1, COLOR_GREEN, COLOR_RED);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);

#ifdef DET
    srand(0);
#else
    srand(time(NULL));
#endif

    world = init_world(4);
    display_world(world);
    key = getch();
    nodelay(stdscr, TRUE);

    while (running) {
        switch (key) {
            case 'z':
            case 'Z':
                if (allowed_direction(NORTH, world.snake.direction))
                    world.snake.direction = NORTH;
                break;
            case 'q':
            case 'Q':
                if (allowed_direction(WEST, world.snake.direction))
                    world.snake.direction = WEST;
                break;
            case 's':
            case 'S':
                if (allowed_direction(SOUTH, world.snake.direction))
                    world.snake.direction = SOUTH;
                break;
            case 'd':
            case 'D':
                if (allowed_direction(EAST, world.snake.direction))
                    world.snake.direction = EAST;
                break;
            case 'p':
            case 'P':
                paused = !paused;
                break;
        }

        if (!paused) {
            if (snake_death(&world)) {
                running = 0;
            } else if (eat_apple(&world)) {
                add_apple_to_world(&world);
            } else {
                move_snake(&world);
            }
        }

        display_world(world);
        key = getch();
        usleep(200000);
        key = getch();
    }

    endwin();
    return 0;
}
