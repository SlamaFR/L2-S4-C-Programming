#include <stdio.h>
#include <string.h>

#include "lecteur.h"
#include "liste.h"
#include "tests.h"

int main(int ac, char **av) {
    if (!test()) {
        printf("Échec des tests !\n");
        return 1;
    }

    return 0;
}
