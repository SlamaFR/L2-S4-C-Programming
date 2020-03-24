#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lecteur.h"
#include "liste.h"
#include "tests.h"
#include "analyseur.h"

int main(int ac, char **av) {
    List list = NULL, wordsList = NULL;
    FILE *file;
    int i, res, lexicographic = 0, occurrences = 0, prefixes = 0, suffixes = 0, expressions = 0;
    char *arg_words = NULL;

    if (!test()) {
        printf("Échec des tests !\n");
        return 1;
    }

    if (ac < 2) return 1;

    file = fopen(av[1], "r");
    if (!file) return 1;

    for (i = 1; i < ac; i++) {
        if (!strcmp(av[i], "-a")) lexicographic = 1;
        else if (!strcmp(av[i], "-n")) occurrences = 1;
        else if (!strcmp(av[i], "-s") && i < ac) {
            suffixes = 1;
            arg_words = av[i + 1];
        } else if (!strcmp(av[i], "-p") && i < ac) {
            prefixes = 1;
            arg_words = av[i + 1];
        } else if (!strcmp(av[i], "-e") && i < ac) {
            expressions = atoi(av[i + 1]);
        }
    }

    /* Lecture intégrale du fichier avec doublons activés. */
    if (!prefixes && !suffixes && !expressions) {
        if (occurrences)
            res = readFileWords(file, &wordsList, BY_OCCURRENCES);
        else if (lexicographic)
            res = readFileWords(file, &wordsList, LEXICOGRAPHIC);
        else
            res = readFileWords(file, &wordsList, NONE);
        if (res) displayWordsOfList(wordsList);
        freeList(&wordsList);
        fclose(file);
        return 0;
    }

    res = readFileWords(file, &wordsList, UNIQUE);
    if (!res) return 1;

    if (prefixes) {
        if (arg_words == NULL) return 1;
        if (occurrences)
            res = groupByPrefixes(wordsList, &list, arg_words, BY_OCCURRENCES);
        else if (lexicographic)
            res = groupByPrefixes(wordsList, &list, arg_words, LEXICOGRAPHIC);
        else
            res = groupByPrefixes(wordsList, &list, arg_words, NONE);
        if (res) displayWordsOfList(list);
        freeList(&wordsList);
        freeList(&list);
        fclose(file);
        return 0;
    } else if (suffixes) {
        if (arg_words == NULL) return 1;
        if (occurrences)
            res = groupBySuffixes(wordsList, &list, arg_words, BY_OCCURRENCES);
        else if (lexicographic)
            res = groupBySuffixes(wordsList, &list, arg_words, LEXICOGRAPHIC);
        else
            res = groupBySuffixes(wordsList, &list, arg_words, NONE);
        if (res) displayWordsOfList(list);
        freeList(&wordsList);
        freeList(&list);
        fclose(file);
        return 0;
    } if (expressions) {
        if (occurrences)
            res = groupByExpressions(wordsList, &list, expressions, BY_OCCURRENCES);
        else if (lexicographic)
            res = groupByExpressions(wordsList, &list, expressions, LEXICOGRAPHIC);
        else
            res = groupByExpressions(wordsList, &list, expressions, NONE);
        if (res) displayWordsOfList(list);
        freeList(&wordsList);
        freeList(&list);
        fclose(file);
        return 0;
    }

    freeList(&list);
    fclose(file);
    return 0;
}
