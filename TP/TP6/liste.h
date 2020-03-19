#ifndef CLM_LISTE_H
#define CLM_LISTE_H

typedef struct cell {
    char *word;
    int occurrences;
    struct cell *next;
    struct cell *previous;
} Cell, *List;

void displayList(List list);

Cell *getWord(List list, char *word);

/**
 * Ajouter un mot à une liste.
 * Si le mot est déjà présent, son nombre d'occurrence est incrémenté.
 * @return Résultat (1 = succès, 0 = échec).
 */
int insertWord(List *list, char *word);

int insertWordAlphabetically(List *list, char *word);

int insertWordByOccurrences(List *list, char *word);

/**
 * Libérer la mémoire d'une liste.
 */
void freeList(List *list);

#endif /* CLM_LISTE_H */
