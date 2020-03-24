#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tests.h"
#include "lecteur.h"
#include "liste.h"

#define NB_TESTS 8

int test_insertWord() {
    List list = NULL;
    char *word1 = "test1", *word2 = "test2";
    Cell *cell;

    int insert_result = insertWord(&list, word1);

    /* Test de l'appel */
    if (insert_result == 0) {
        printf("[TEST] insertWord() : Erreur test n°1 !\n");
        return 0;
    }

    /* Test de l'insertion */
    if (list == NULL) {
        printf("[TEST] insertWord() : Erreur test n°2 !\n");
        return 0;
    }

    cell = list;

    /* Test de la copie du mot */
    if (strcmp(word1, cell->word) != 0) {
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

    /* Test de la mise à jour du nombre d'occurrences */
    insertWord(&list, word1);
    if (cell->occurrences != 2) {
        printf("[TEST] insertWord() : Erreur test n°6 !\n");
        return 0;
    }

    /* Test de l'insertion d'un deuxième mot différent */
    insert_result = insertWord(&list, word2);
    if (insert_result == 0) {
        printf("[TEST] insertWord() : Erreur test n°7 !\n");
        return 0;
    }

    cell = list;

    /* Test de la position du nouveau mot en tête */
    if (strcmp(cell->word, word2) != 0) {
        printf("[TEST] insertWord() : Erreur test n°8 !\n");
        return 0;
    }

    return 1;
}

int test_insertWordAlphabetically() {
    List list = NULL;
    char *word1 = "avion", *word2 = "bateau", *word3 = "automobile";
    Cell *cell;

    int insert_result1 = insertWordAlphabetically(&list, word1);
    int insert_result2 = insertWordAlphabetically(&list, word2);
    int insert_result3 = insertWordAlphabetically(&list, word3);

    /* Test de l'appel n°1 */
    if (insert_result1 == 0) {
        printf("[TEST] insertWordAlphabetically() : Erreur test n°1 !\n");
        return 0;
    }

    /* Test de l'appel n°2 */
    if (insert_result2 == 0) {
        printf("[TEST] insertWordAlphabetically() : Erreur test n°2 !\n");
        return 0;
    }

    /* Test de l'appel n°3 */
    if (insert_result3 == 0) {
        printf("[TEST] insertWordAlphabetically() : Erreur test n°3 !\n");
        return 0;
    }

    cell = getWord(list, word1);

    if (cell == NULL) {
        printf("[TEST] insertWordAlphabetically() : Erreur test n°4 !\n");
        return 0;
    }

    if (strcmp(cell->word, cell->next->word) >= 0) {
        printf("[TEST] insertWordAlphabetically() : Erreur test n°4 !\n");
        return 0;
    }

    if (strcmp(cell->word, cell->previous->word) <= 0) {
        printf("[TEST] insertWordAlphabetically() : Erreur test n°5 !\n");
        return 0;
    }

    return 1;
}

int test_insertWordByOccurrences() {
    List list = NULL;
    char *word1 = "test1", *word2 = "test2", *word3 = "test3";
    Cell *cell;

    int insert_result = insertWordByOccurrences(&list, word1);

    /* Test de l'appel */
    if (insert_result == 0) {
        printf("[TEST] insertWordByOccurrences() : Erreur test n°1 !\n");
        return 0;
    }

    insertWordByOccurrences(&list, word1);
    insertWordByOccurrences(&list, word1);
    insertWordByOccurrences(&list, word3);
    insertWordByOccurrences(&list, word2);
    insertWordByOccurrences(&list, word2);

    /*
     * word1 = 3,
     * word2 = 2,
     * word3 = 1.
     */

    cell = getWord(list, word2);

    if (cell->occurrences != 2) {
        printf("[TEST] insertWordByOccurrences() : Erreur test n°2 !\n");
        return 0;
    }

    if (cell->next->occurrences != 1) {
        printf("[TEST] insertWordByOccurrences() : Erreur test n°3 !\n");
        return 0;
    }

    if (cell->previous->occurrences != 3) {
        printf("[TEST] insertWordByOccurrences() : Erreur test n°4 !\n");
        return 0;
    }

    return 1;
}

int test_getWord() {
    List list = NULL;
    char *word = "test";
    Cell *cell;

    insertWord(&list, word);
    cell = getWord(list, word);

    /* Vérification du résultat */
    if (strcmp(word, cell->word) != 0) {
        printf("[TEST] getWord() : Erreur test n°1 !\n");
        return 0;
    }

    return 1;
}

int test_readFileByWords(){
    List list = NULL;
    FILE *file;
    file = fopen("texte.txt", "r");
    int none_result, lexicographic_result, occurence_result;
    
    none_result = readFileByWords(file, &list, NONE);
    lexicographic_result = readFileByWords(file, &list, LEXICOGRAPHIC);
    occurence_result = readFileByWords(file, &list, BY_OCCURRENCES);
    
    if (none_result == 0 || lexicographic_result == 0 || occurence_result == 0) {
        printf("[TEST] readFileByWords() : Erreur test n°1 !\n");
        return 0;
    }
    return 1;
}

int test_readFileByWordsSuffixes(){
    List list = NULL;
    List list2 = NULL;
    char *word = "test";
    FILE *file;
    int none_result, lexicographic_result, occurence_result;
    file = fopen("test.ascii", "r");
    
    none_result = readFileByWordsSuffixes(file, &list, &list2, word,   NONE);
    lexicographic_result = readFileByWordsSuffixes(file, &list, &list2, word, LEXICOGRAPHIC );
    occurence_result = readFileByWordsSuffixes(file, &list, &list2, word, BY_OCCURRENCES );
    
    if (none_result == 0 || lexicographic_result == 0 || occurence_result == 0) {
        printf("[TEST] readFileByWordsSuffixes() : Erreur test n°1 !\n");
        return 0;
    }
    return 1;
    
}

int test_readFileByWordsPrefixes(){
    List list = NULL;
    List list2 = NULL;
    char *word = "test";
    FILE *file;
    int none_result, lexicographic_result, occurence_result;
    file = fopen("test.ascii", "r");
    
    
    none_result = readFileByWordsPrefixes(file, &list, &list2, word,   NONE);
    lexicographic_result = readFileByWordsPrefixes(file, &list, &list2, word, LEXICOGRAPHIC );
    occurence_result = readFileByWordsPrefixes(file, &list, &list2, word, BY_OCCURRENCES );
    
    if (none_result == 0 || lexicographic_result == 0 || occurence_result == 0) {
        printf("[TEST] readFileByWordsPrefixes() : Erreur test n°1 !\n");
        return 0;
    }
    return 1;
}

int test_readFileByExpressions(){
    List list = NULL;
    List list2 = NULL;
    FILE *file;
    int none_result, lexicographic_result, occurence_result;
    file = fopen("test.ascii", "r");
    
    none_result = readFileByExpressions(file, &list, &list2, NONE, 2);
    lexicographic_result = readFileByExpressions(file, &list, &list2, LEXICOGRAPHIC, 2);
    occurence_result = readFileByExpressions(file, &list, &list2, BY_OCCURRENCES, 2);
    
    if (none_result == 0 || lexicographic_result == 0 || occurence_result == 0) {
        printf("[TEST] readFileByWordsExpressions() : Erreur test n°1 !\n");
        return 0;
    }
    return 1;
}

int test() {
    int (*tests[NB_TESTS])() = {
            &test_insertWord,
            &test_insertWordAlphabetically,
            &test_insertWordByOccurrences,
            &test_getWord,
            &test_readFileByWords,
            &test_readFileByWordsSuffixes,
            &test_readFileByWordsPrefixes,
            &test_readFileByExpressions
    }, i, result = 1;

    for (i = 0; i < NB_TESTS; i++) {
        if (tests[i]() != 1) result = 0;
    }

    return result;
}
