#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "liste.h"

void displayList(List list) {
    Cell *c = list;
    int i;
    for (i = 0; i < 20 && c; i++) {
        printf("Cell{\"%s\":%d} -> ", c->word, c->occurrences);
        c = c->next;
    }
    printf("NULL\n");
}

Cell *getWord(List list, char *word) {
    Cell *current;
    for (current = list; current; current = current->next) {
        if (strcmp(word, current->word) == 0)
            return current;
    }
    return NULL;
}

int insertWord(List *list, char *word) {
    Cell *cell = NULL;

    if ((cell = getWord(*list, word)) != NULL) {
        cell->occurrences++;
        return 1;
    }

    cell = (Cell *) malloc(sizeof(Cell));
    if (!cell) return 0;
    cell->occurrences = 1;
    cell->word = (char *) malloc(strlen(word));
    cell->next = NULL;
    cell->previous = NULL;
    strcpy(cell->word, word);

    if (*list) {
        cell->next = *list;
        (*list)->previous = cell;
    }
    *list = cell;

    return 1;
}

int insertWordAlphabetically(List *list, char *word) {
    Cell *current = *list, *cell = NULL, *precedent = NULL;

    if ((cell = getWord(*list, word)) != NULL) {
        cell->occurrences++;
        return 1;
    }

    cell = (Cell *) malloc(sizeof(Cell));
    if (!cell) return 0;
    cell->occurrences = 1;
    cell->word = (char *) malloc(strlen(word));
    cell->next = NULL;
    cell->previous = NULL;
    strcpy(cell->word, word);

    if (!current) {
        *list = cell;
    } else {
        while (current != NULL && strcmp(word, current->word) > 0) {
            precedent = current;
            current = current->next;
        }
        if (precedent != NULL) {
            cell->next = current;
            if (current) current->previous = cell;
            precedent->next = cell;
            cell->previous = precedent;
        } else {
            cell->next = *list;
            (*list)->previous = cell;
            *list = cell;
        }
    }
    return 1;
}

int insertWordByOccurrences(List *list, char *word) {
    Cell *current = *list, *cell = NULL, *precedent = NULL;

    if ((cell = getWord(*list, word)) != NULL) {
        cell->occurrences++;
        if (cell->next) cell->next->previous = cell->previous;
        if (cell->previous) cell->previous->next = cell->next;
    } else {
        cell = (Cell *) malloc(sizeof(Cell));
        if (!cell) return 0;
        cell->occurrences = 1;
        cell->word = (char *) malloc(strlen(word));
        cell->next = NULL;
        cell->previous = NULL;
        strcpy(cell->word, word);
    }

    if (!current) {
        *list = cell;
    } else {
        while (current != NULL && current->occurrences > cell->occurrences) {
            precedent = current;
            current = current->next;
        }
        if (precedent != NULL) {
            cell->next = (cell == current ? NULL : current);
            if (current) current->previous = cell;
            precedent->next = cell;
            cell->previous = precedent;
        } else {
            cell->next = (cell == current ? NULL : current);
            current->previous = cell;
            *list = cell;
        }
    }
    return 1;
}

void freeList(List *list) {
    Cell *cell;
    for (cell = *list; cell; cell = cell->next)
        free(cell);
}
