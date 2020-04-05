#include "Grille.h"

char gen_aleatoire() {
    int alea = 1 + rand() % 47;

    if (0 < alea && alea <= 11)
        return 'E';

    else if (11 < alea && alea <= 19)
        return 'T';

    else if (19 < alea && alea <= 26) {

        int alea2 = 1 + rand() % 5;

        switch (alea2) {
            case 1:
                return 'A';
            case 2:
                return 'I';
            case 3:
                return 'N';
            case 4:
                return 'O';
            case 5:
                return 'S';
            default:
                return '0';
        }
    } else if (26 < alea && alea <= 32)
        return 'R';

    else if (32 < alea && alea <= 37)
        return 'H';

    else if (37 < alea && alea <= 41) {

        int alea2 = 1 + rand() % 2;

        if (alea2 == 1)
            return 'D';
        else if (alea2 == 2)
            return 'L';
        else
            return '0';
    } else if (41 < alea && alea <= 44) {

        int alea2 = 1 + rand() % 3;

        switch (alea2) {
            case 1:
                return 'C';
            case 2:
                return 'M';
            case 3:
                return 'U';
            default:
                return '0';
        }
    } else if (alea == 45 || alea == 46) {

        int alea2 = 1 + rand() % 6;

        switch (alea2) {
            case 1:
                return 'B';
            case 2:
                return 'F';
            case 3:
                return 'G';
            case 4:
                return 'P';
            case 5:
                return 'W';
            case 6:
                return 'Y';
            default:
                return '0';
        }
    } else if (alea == 47) {

        int alea2 = 1 + rand() % 6;

        switch (alea2) {
            case 1:
                return 'J';
            case 2:
                return 'K';
            case 3:
                return 'Q';
            case 4:
                return 'V';
            case 5:
                return 'X';
            case 6:
                return 'Z';
            default:
                return '0';
        }
    } else
        return '0';
}


int rempli_grille(ListCase grille) {

    int i;
    char lettre;

    assert(grille != NULL);

    for (i = 1; i < 16; i++) {
        do {
            lettre = gen_aleatoire();
        } while (lettre == '0');
        alloue_case(grille, lettre);

    }

    return 1;
}


Case init_grille() {

    char lettre;
    Case grille;

    do {
        lettre = gen_aleatoire();
    } while (lettre == '0');

    grille.lettre = lettre;
    grille.passe = 1;
    grille.valide = 0;
    grille.x = 0;
    grille.y = 0;
    grille.suivant = NULL;

    return grille;
}


int alloue_case(ListCase grille, char lettre) {

    ListCase cases = (ListCase) malloc(sizeof(Case));
    ListCase actuel = grille;

    if (NULL == cases)
        return 0;

    while (actuel->suivant != NULL) {
        actuel = actuel->suivant;
    }

    cases->lettre = lettre;
    cases->passe = 0;
    cases->valide = 0;
    cases->suivant = NULL;
    actuel->suivant = cases;

    return 1;
}


void affiche_grille(const ListCase grille) {

    ListCase actuel = grille;

    assert(grille != NULL);

    while (actuel != NULL) {
        actuel = actuel->suivant;
    }

    return;
}
