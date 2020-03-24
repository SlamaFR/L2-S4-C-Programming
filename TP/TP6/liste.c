#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "liste.h"

void displayWordsOfList(List list) {
    Cell *current;
    for (current = list; current != NULL; current = current->next)
        printf("%s  %d\n", current->word, current->occurrences);
}

Cell *getWord(List list, char *word) {
    Cell *current;
    for (current = list; current; current = current->next) {
        if (strcmp(word, current->word) == 0)
            return current;
    }
    return NULL;
}

int insertWord(List *list, char *word, int unique) {
    Cell *cell = NULL;

    if ((cell = getWord(*list, word)) != NULL && !unique) {
        cell->occurrences++;
        return 1;
    }

    cell = (Cell *) malloc(sizeof(Cell));
    if (!cell) return 0;
    cell->occurrences = 1;
    cell->word = (char *) malloc(strlen(word) + 1);
    if (!cell->word) return 0;
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

int insertWordUnsorted(List *list, char *word) {
    Cell *cell = NULL;

    cell = (Cell *) malloc(sizeof(Cell));
    if (!cell) return 0;
    cell->occurrences = 1;
    cell->word = (char *) malloc(strlen(word));
    if (!cell->word) return 0;
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
    if (!cell->word) return 0;
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
    Cell *current = *list, *cell = NULL, *tmp = NULL;

    if ((cell = getWord(*list, word)) != NULL) {
        cell->occurrences++;

        /* Décalage vers la tête (gauche) */
        while (cell->previous != NULL && cell->previous->occurrences < cell->occurrences) {
            tmp = cell->previous;

            tmp->next = cell->next;
            cell->previous = tmp->previous;
            cell->next = tmp;
            tmp->previous = cell;

            if (cell->previous) cell->previous->next = cell;
            else *list = cell;

            if (tmp->next) tmp->next->previous = tmp;
        }
    } else {
        cell = (Cell *) malloc(sizeof(Cell));
        if (!cell) return 0;
        cell->occurrences = 1;
        cell->word = (char *) malloc(strlen(word));
        if (!cell->word) return 0;
        cell->next = NULL;
        cell->previous = NULL;
        strcpy(cell->word, word);

        while (current && current->occurrences > cell->occurrences) {
            tmp = current;
            current = current->next;
        }

        if (tmp == NULL) {
            cell->next = *list;
            if (*list) (*list)->previous = cell;
            *list = cell;
        } else {
            cell->next = current;
            if (current)current->previous = cell;
            tmp->next = cell;
            cell->previous = tmp;
        }
    }
    return 1;
}

void freeList(List *list) {
    Cell *cell;
    for (cell = *list; cell; cell = cell->next)
        free(cell);
}
