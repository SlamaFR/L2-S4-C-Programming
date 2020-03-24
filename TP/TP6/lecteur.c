#include <stdlib.h>
#include <ctype.h>
#include <string.h>


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
                        insertWordUnsorted(list, word);
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

int readFileByWordsSuffixes(FILE *file, List *list, List *list2, char *word, SortType sort) {
    
    Cell *cell = NULL;
    Cell *current;
    
    if (NULL == (cell = getWord(*list, word)))
        return 0;
    
    for (current = *list; current; current = current->next) {
        if (strcmp(word, current->word) == 0){
            if (current->previous != NULL){
                switch (sort) {
                    case NONE:
                        insertWord(list2, current->previous->word);
                        break;
                    case LEXICOGRAPHIC:
                        insertWordAlphabetically(list2, current->previous->word);
                        break;
                    case BY_OCCURRENCES:
                        insertWordByOccurrences(list2, current->previous->word);
                        break;
                    default:
                        return 0;
                }
            }
        }
    }
    return 1;
}

int readFileByWordsPrefixes(FILE *file, List *list, List *list2, char *word, SortType sort) {
    
    Cell *cell = NULL;
    Cell *current;
    
    if (NULL == (cell = getWord(*list, word)))
        return 0;
    
    for (current = *list; current; current = current->next) {
        if (strcmp(word, current->word) == 0){
            if (current->next != NULL){
                switch (sort) {
                    case NONE:
                        insertWord(list2, current->next->word);
                        break;
                    case LEXICOGRAPHIC:
                        insertWordAlphabetically(list2, current->next->word);
                        break;
                    case BY_OCCURRENCES:
                        insertWordByOccurrences(list2, current->next->word);
                        break;
                    default:
                        return 0;
                }
            }
        }
    }
    return 1;
}

int readFileByExpressions(FILE *file, List *list, List *list2, SortType sort, int n) {
    
    Cell *current;
    Cell *current2;
    Cell *current3;
    char *wordCat = NULL;

    int i;
    i = 2;
    
    current = *list;
    current2 = *list;
    
    while (i < n){
        current2 = current2->next;
        i++;
    }
    
    
    while (current->next != NULL)
        current = current->next;
    
    current3 = current;
    
    while (current != current2) {
        
        wordCat = (char *) malloc(sizeof(char)* strlen(current->word));
        strcpy(wordCat,current->word);
        current3 = current3->previous;
        
        for (i = 1; i < n; i++){
            wordCat = (char *)realloc(wordCat, sizeof(char)* (strlen(wordCat)+strlen(current3->word)));
            strcat(wordCat, " ");
            strcat(wordCat, current3->word);
            current3 = current3->previous;
        }
        
        if (sort == NONE){
            printf("NONE");
            insertWord(list2, wordCat);
        }
        else if (sort == LEXICOGRAPHIC)
            insertWordAlphabetically(list2, wordCat);
        
        else if (sort == BY_OCCURRENCES)
            insertWordByOccurrences(list2, wordCat);
       
        
        free(wordCat);
        wordCat = NULL;
        
        current = current->previous;
        current3 = current;
    }
    return 1;
}
