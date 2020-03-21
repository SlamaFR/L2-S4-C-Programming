#include <stdio.h>
#include <string.h>

#include "lecteur.h"
#include "liste.h"
#include "tests.h"

int main(int ac, char **av) {
    List list = NULL;
    FILE *file;

    if (!test()) {
        printf("Échec des tests !\n");
        return 1;
    }

    file = fopen("test.ascii", "r");
    readFileByWords(file, &list, NONE);
    displayList(list);

    list = NULL;
    fseek(file, SEEK_SET, 0);

    readFileByWords(file, &list, LEXICOGRAPHIC);
    displayList(list);

    list = NULL;
    fseek(file, SEEK_SET, 0);

    readFileByWords(file, &list, BY_OCCURRENCES);
    displayList(list);

    return 0;
}
