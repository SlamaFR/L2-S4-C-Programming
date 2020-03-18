#ifndef CLM_HACHAGE_H
#define CLM_HACHAGE_H

#define N 10000

typedef struct cell {
    char *word;
    int occurrences;
    struct cell *next;
} Cell, *List;

/**
 * Transformer un mot p en un entier.
 */
unsigned int hash(char *word);

/**
 * Ajouter un mot à la liste des mots de même hachage.
 * @param hashTable Table de hachage.
 * @param word Mot à ajouter.
 * @return Résultat (1 = succès, 0 = échec).
 */
int insertWord(List hashTable[N], char *word);

/**
 * Libérer la mémoire d'une liste.
 */
void freeList(List *list);

#endif //CLM_HACHAGE_H
