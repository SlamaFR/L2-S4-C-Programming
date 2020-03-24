#include <stdio.h>
#include "liste.h"

#ifndef CLM_LECTEUR_H
#define CLM_LECTEUR_H

typedef enum {
    UNIQUE,             /* Chaque mot du texte possède une case unique. */
    LEXICOGRAPHIC,      /* Les cases sont triées par ordre lexicographique. */
    BY_OCCURRENCES,     /* Les cases sont triées par ordre d'occurrences. */
    NONE                /* Les cases ne sont pas triées. */
} SortType;

int readFileWords(FILE *file, List *list, SortType sort);

#endif /* CLM_LECTEUR_H */
