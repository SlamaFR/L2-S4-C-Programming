#include <string.h>
#include <stdlib.h>
#include "analyseur.h"
#include "liste.h"
#include "lecteur.h"

int groupBySuffixes(List wordsList, List *list, char *word, SortType sort) {
    Cell *current;

    if (getWord(wordsList, word) == NULL)
        return 0;

    for (current = wordsList; current; current = current->next) {
        if (strcmp(word, current->word) == 0) {
            if (current->previous != NULL) {
                switch (sort) {
                    case NONE:
                        insertWord(list, current->previous->word, 0);
                        break;
                    case LEXICOGRAPHIC:
                        insertWordAlphabetically(list, current->previous->word);
                        break;
                    case BY_OCCURRENCES:
                        insertWordByOccurrences(list, current->previous->word);
                        break;
                    default:
                        return 0;
                }
            }
        }
    }
    return 1;
}

int groupByPrefixes(List wordsList, List *list, char *word, SortType sort) {
    Cell *current;

    if (getWord(wordsList, word) == NULL)
        return 0;

    for (current = wordsList; current; current = current->next) {
        if (strcmp(word, current->word) == 0) {
            if (current->next != NULL) {
                switch (sort) {
                    case NONE:
                        insertWord(list, current->next->word, 0);
                        break;
                    case LEXICOGRAPHIC:
                        insertWordAlphabetically(list, current->next->word);
                        break;
                    case BY_OCCURRENCES:
                        insertWordByOccurrences(list, current->next->word);
                        break;
                    default:
                        return 0;
                }
            }
        }
    }
    return 1;
}

int groupByExpressions(List wordsList, List *list, int n, SortType sort) {
    Cell *current = wordsList, *cursor;
    int i;
    char *expression;

    while (current->next) current = current->next;

    while (current->previous) {
        expression = NULL;

        cursor = current;
        for (i = 0; i < n; i++) {
            expression = realloc(expression, sizeof(expression) + sizeof(cursor->word) + sizeof(char));
            if (expression == NULL)
                return 0;

            strcat(expression, cursor->word);
            strcat(expression, " ");
            cursor = cursor->previous;

            if (cursor == NULL) break;
        }
        strcat(expression, "\0");

        if (i + 1 < n) break;

        switch (sort) {
            case NONE:
                insertWord(list, expression, 0);
                break;
            case LEXICOGRAPHIC:
                insertWordAlphabetically(list, expression);
                break;
            case BY_OCCURRENCES:
                insertWordByOccurrences(list, expression);
                break;
            default:
                return 0;
        }
        current = current->previous;
    }
    return 1;



























    /*
    Cell *current;
    Cell *current2;
    Cell *current3;
    char *wordCat = NULL;

    int i;
    i = 2;

    current = wordsList;
    current2 = wordsList;

    while (i < n) {
        current2 = current2->next;
        i++;
    }


    while (current->next != NULL)
        current = current->next;

    current3 = current;

    while (current != current2) {

        wordCat = (char *) malloc(sizeof(char) * strlen(current->word));
        strcpy(wordCat, current->word);
        current3 = current3->previous;

        for (i = 1; i < n; i++) {
            wordCat = (char *) realloc(wordCat, sizeof(char) * (strlen(wordCat) + strlen(current3->word)));
            strcat(wordCat, " ");
            strcat(wordCat, current3->word);
            current3 = current3->previous;
        }

        switch (sort) {
            case NONE:
                insertWord(list, wordCat, 0);
                break;
            case LEXICOGRAPHIC:
                insertWordAlphabetically(list, wordCat);
                break;
            case BY_OCCURRENCES:
                insertWordByOccurrences(list, wordCat);
                break;
            default:
                continue;
        }
        free(wordCat);

        current = current->previous;
        current3 = current;
    }
    return 1;
     */
}
