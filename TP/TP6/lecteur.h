#include <stdio.h>
#include "liste.h"

#ifndef CLM_LECTEUR_H
#define CLM_LECTEUR_H

typedef enum {
    LEXICOGRAPHIC,
    BY_OCCURRENCES,
    NONE
} SortType;

int readFileByWords(FILE *file, List *list, SortType sort);

int readFileByWordsSuffixes(FILE *file, List *list, List *list2, char *word, SortType sort);

int readFileByWordsPrefixes(FILE *file, List *list, List *list2, char *word, SortType sort);

int readFileByExpressions(FILE *file, List *list, List *list2, SortType sort, int n);

#endif /* CLM_LECTEUR_H */
