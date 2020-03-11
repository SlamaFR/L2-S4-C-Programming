#include <stdlib.h>
#include "Serpent.h"

int insert_head(SnakeList *list, Cell cell) {
    SnakeCell *snakeCell = (SnakeList) malloc(sizeof(SnakeCell));

    if (snakeCell == NULL)
        return 0;

    snakeCell->next = *list;
    snakeCell->snake_cell = cell;
    *list = snakeCell;
    return 1;
}

void remove_tail(SnakeList *list) {
    SnakeList snakeList = *list;

    if (snakeList == NULL)
        return;

    if (snakeList->next == NULL) {
        free(snakeList);
        *list = NULL;
        return;
    }

    for (; snakeList->next->next; snakeList = snakeList->next);
    free(snakeList->next);
    snakeList->next = NULL;
}
