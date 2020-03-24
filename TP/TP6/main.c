#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "lecteur.h"
#include "liste.h"
#include "tests.h"

int main(int ac, char **av) {
    List list = NULL;
    List listWords = NULL;
    
    FILE *file;

    if (!test()) {
        printf("Échec des tests !\n");
        return 1;
    }
    
    file = fopen(av[1] , "r");
    /* Liste chainée avec les mots dans l'ordre du fichier*/
    readFileByWords(file, &list, LEXICOGRAPHIC);
    displayWordsOfList(list);
    
    assert(av[2] != NULL);
    
    if (strcmp(av[2],"-a") == 0)
        readFileByWords(file, &listWords, LEXICOGRAPHIC);

    if (strcmp(av[2],"-n") == 0)
    readFileByWords(file, &listWords, BY_OCCURRENCES);

    if (strcmp(av[2],"-s") == 0){
        if (av[4] != NULL){
            if (strcmp(av[4],"-a"))
                readFileByWordsSuffixes(file, &list, &listWords, av[3], LEXICOGRAPHIC);
            else if (strcmp(av[4],"-n"))
                readFileByWordsSuffixes(file, &list, &listWords, av[3], BY_OCCURRENCES);
        }
        else
            readFileByWordsSuffixes(file, &list, &listWords, av[3], NONE);
    }

    if (strcmp(av[2],"-p") == 0){
        if (av[4] != NULL){
            if (strcmp(av[4],"-a"))
                readFileByWordsPrefixes(file, &list, &listWords, av[3], LEXICOGRAPHIC);
            else if (strcmp(av[4],"-n"))
                readFileByWordsPrefixes(file, &list, &listWords, av[3], BY_OCCURRENCES);
        }
        else
            readFileByWordsPrefixes(file, &list, &listWords, av[3], NONE);
    }

    if (strcmp(av[2],"-e") == 0){
        if (av[4] != NULL){
            if (strcmp(av[4],"-a"))
                readFileByExpressions(file, &list, &listWords,LEXICOGRAPHIC , 2);
            else if (strcmp(av[4],"-n"))
                readFileByExpressions(file, &list, &listWords, atoi(av[3]), BY_OCCURRENCES);
        }

        else
            readFileByExpressions(file, &list, &listWords, atoi(av[3]), NONE);
    }

    
//    displayWordsOfList(listWords);
    
    
    

    
    return 0;
}
