#include "Monde.h"
#include "Serpent.h"
#include <assert.h>

int empty_cell(World world, Cell cell) {
    AppleCell *apple;
    for (apple = world.apples; apple != NULL; apple = apple->next) {
        if (cell.x != apple->apple.apple_cell.x)
            continue;
        if (cell.y != apple->apple.apple_cell.y)
            continue;
        return 0;
    }
    return 1;
}

int snake_in_cell(World world, Cell cell) {
    SnakeCell *serpent;
    for (serpent = world.snake.body; serpent && serpent->next; serpent = serpent->next) {
        if (cell.x != serpent->snake_cell.x)
            continue;
        if (cell.y != serpent->snake_cell.y)
            continue;
        return 1;
    }
    return 0;
}

int cell_in_world(World world, Cell cell) {
    if (cell.x < 0 || cell.x >= world.width)
        return 0;
    if (cell.y < 0 || cell.y >= world.height)
        return 0;
    return 1;
}

Cell next_cell(Cell cell, Direction direction) {
    Cell next_cell;
    switch (direction) {
        case SOUTH:
            next_cell.x = cell.x;
            next_cell.y = cell.y + 1;
            break;
        case NORTH:
            next_cell.x = cell.x;
            next_cell.y = cell.y - 1;
            break;
        case EAST:
            next_cell.x = cell.x + 1;
            next_cell.y = cell.y;
            break;
        case WEST:
            next_cell.x = cell.x - 1;
            next_cell.y = cell.y;
            break;
        default:
            return cell;
    }
    return next_cell;
}

int move_snake(World *world) {
    Cell cell;
    assert(world != NULL);
    assert(world->snake.body != NULL);

    cell = next_cell(world->snake.body->snake_cell, world->snake.direction);
    if (!empty_cell(*world, cell) || !cell_in_world(*world, cell) || snake_in_cell(*world, cell))
        return 0;

    insert_head(&world->snake.body, cell);
    remove_tail(&world->snake.body);
    return 1;
}

int eat_apple(World *world) {
    Cell cell;
    AppleList lst, precedent = NULL;
    assert(world != NULL);
    assert(world->snake.body != NULL);

    cell = next_cell(world->snake.body->snake_cell, world->snake.direction);
    if (empty_cell(*world, cell) || !cell_in_world(*world, cell) || snake_in_cell(*world, cell))
        return 0;

    if (world->apples != NULL)
        for (lst = world->apples; lst; lst = lst->next) {
            if (equals_cells(lst->apple.apple_cell, cell)) {
                if (precedent) {
                    precedent->next = lst->next;
                } else {
                    world->apples = lst->next;
                }
                free(lst);
                break;
            }
            precedent = lst;
        }

    insert_head(&world->snake.body, cell);
    world->eaten_apple_amount++;
    return 1;
}

int snake_death(World *world) {
    Cell cell;
    assert(world != NULL);
    assert(world->snake.body != NULL);

    cell = next_cell(world->snake.body->snake_cell, world->snake.direction);
    return (!cell_in_world(*world, cell) || snake_in_cell(*world, cell));
}


Snake init_snake(World mon) {
    Snake serpent;
    int centre_x, centre_y, i;

    centre_x = mon.width / 2;
    centre_y = mon.height / 2;

    serpent.direction = EAST;
    serpent.body = NULL;

    for (i = 0; i < 4; i++) {
        insert_head(&serpent.body, create_cell(centre_x - 4 + i, centre_y));
    }

    return serpent;
}

int add_apple_to_world(World *mon) {
    AppleList *lst = &mon->apples, apple;
    SnakeList serpent;
    Apple p;
    int correct;

    AppleList cellulePomme = (AppleList) malloc(sizeof(AppleCell));

    if (cellulePomme == NULL)
        return 0;

    do {
        p = generate_random_apple(mon->height, mon->width);
        correct = 1;
        if (*lst != NULL)
            for (apple = *lst; apple; apple = apple->next) {
                if (equals_cells(p.apple_cell, apple->apple.apple_cell)) {
                    correct = 0;
                    break;
                }
            }
        if (mon->snake.body != NULL)
            for (serpent = mon->snake.body; serpent; serpent = serpent->next) {
                if (equals_cells(p.apple_cell, serpent->snake_cell)) {
                    correct = 0;
                    break;
                }
            }
    } while (!correct);

    cellulePomme->apple = p;
    cellulePomme->next = *lst;
    *lst = cellulePomme;
    return 1;
}

World init_world(int apples_amount) {
    World world;
    int i;

    world.width = 16;
    world.height = 8;
    world.eaten_apple_amount = 0;
    world.apples = NULL;

    for (i = 0; i < apples_amount; i++)
        add_apple_to_world(&world);

    world.snake = init_snake(world);

    return world;
}
