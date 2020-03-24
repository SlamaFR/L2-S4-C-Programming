#include "liste.h"
#include "lecteur.h"

#ifndef CLM_ANALYSEUR_H
#define CLM_ANALYSEUR_H

int groupBySuffixes(List wordsList, List *list, char *word, SortType sort);

int groupByPrefixes(List wordsList, List *list, char *word, SortType sort);

int groupByExpressions(List wordsList, List *list, int n, SortType sort);

#endif /* CLM_ANALYSEUR_H */
