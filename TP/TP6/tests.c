#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tests.h"
#include "lecteur.h"
#include "hachage.h"
#include "tri.h"

#define NB_TESTS 1

int test_insertWord() {
    List hashTable[N] = {NULL};
    char *word = "test";
    unsigned int word_hash = hash(word);
    Cell *cell;

    int insert_result = insertWord(hashTable, word);

    /* Test de l'appel */
    if (insert_result == 0) {
        printf("[TEST] insertWord() : Erreur test n°1 !\n");
        return 0;
    }

    cell = hashTable[word_hash % N];

    /* Test de l'insertion */
    if (cell == NULL) {
        printf("[TEST] insertWord() : Erreur test n°2 !\n");
        return 0;
    }

    /* Test de la copie du mot */
    if (strcmp(word, cell->word) != 0) {
        printf("[TEST] insertWord() : Erreur test n°3 !\n");
        return 0;
    }

    /* Test de l'initialisation du nombre d'occurrence */
    if (cell->occurrences != 1) {
        printf("[TEST] insertWord() : Erreur test n°4 !\n");
        return 0;
    }

    /* Test de l'initialisation de la cellule suivante */
    if (cell->next != NULL) {
        printf("[TEST] insertWord() : Erreur test n°5 !\n");
        return 0;
    }

    /* Test de la mise à jour de nombre d'occurrences */
    insertWord(hashTable, word);
    if (cell->occurrences != 2) {
        printf("[TEST] insertWord() : Erreur test n°4 !\n");
        return 0;
    }

    return 1;
}

int test() {
    int functions[] = {
            test_insertWord()
    }, i;

    for (i = 0; i < NB_TESTS; i++) {
        if (functions[i] != 1) return 0;
    }

    printf("[TEST] Tous les tests sont passés avec succès !\n");
    return 1;
}