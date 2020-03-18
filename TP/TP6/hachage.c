#include <stdlib.h>
#include <string.h>
#include "hachage.h"

unsigned int hash(char *word) {
    unsigned int h = 0, g;
    for (; *word; word++) {
        h = (h << (unsigned int) 4) + *word;
        if ((g = h & 0xf0000000)) {
            h = h ^ (g >> (unsigned int) 24);
            h = h ^ g;
        }
    }
    return h;
}

int insertWord(List hashTable[N], char *word) {
    unsigned int h = hash(word);
    List *list = &hashTable[h % N];
    Cell *current, *cell = NULL;

    for (current = *list; current; current = current->next) {
        if (!strcmp(current->word, word)) {
            current->occurrences++;
            return 1;
        }
    }

    cell = (Cell *) malloc(sizeof(Cell));
    if (!cell) return 0;
    cell->occurrences = 1;
    cell->word = (char *) malloc(strlen(word));
    cell->next = NULL;
    strcpy(cell->word, word);

    if (*list != NULL)
        cell->next = *list;
    *list = cell;

    return 1;
}

void freeList(List *list) {
    Cell *cell;
    for (cell = *list; cell; cell = cell->next)
        free(cell);
}
