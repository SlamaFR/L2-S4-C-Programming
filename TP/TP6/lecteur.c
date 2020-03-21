#include <stdlib.h>
#include <ctype.h>

#include "lecteur.h"
#include "liste.h"

int readFileByWords(FILE *file, List *list, SortType sort) {
    int charPos = 0, currentWordPos = 0;
    char *word = NULL, *tmp = NULL, current = 0;
    size_t size = 0;

    word = (char *) malloc(0);
    if (!word)
        return 0;

    while ((current = (char) fgetc(file)) && current != EOF) {
        if (current != ' ' && current != '\n' && current != '\t' && current != '.' && current != ';' &&
            current != ',' && current != '?' && current != '!') {

            size++;
            tmp = (char *) realloc(word, size + 2);
            if (!tmp) {
                free(word);
                return 0;
            }
            word = tmp;
            word[charPos - currentWordPos] = (char) tolower(current);
        } else {
            if (word) {
                word[charPos - currentWordPos] = '\0';
                switch (sort) {
                    case NONE:
                        insertWord(list, word);
                        break;
                    case LEXICOGRAPHIC:
                        insertWordAlphabetically(list, word);
                        break;
                    case BY_OCCURRENCES:
                        insertWordByOccurrences(list, word);
                        break;
                    default:
                        free(word);
                        return 0;
                }
                free(word);
                word = NULL;
            }
            currentWordPos = charPos + 1;
            size = 0;
        }
        charPos++;
    }
    return 1;
}

int readFileByWordsSuffixes(FILE *file, List *list, SortType sort) {
    return 1;
}

int readFileByWordsPrefixes(FILE *file, List *list, SortType sort) {
    return 1;
}

int readFileByExpressions(FILE *file, List *list, SortType sort, int n) {
    return 1;
}
