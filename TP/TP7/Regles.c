#include "Regles.h"
#include <ctype.h>

int deplacement_valide(char touch, ListCase grille) {

    ListCase actuel = grille;

    assert(NULL != grille);

    while (actuel->passe != 1) {
        actuel = actuel->suivant;
    }

    switch (touch) {
        case 'z' :
            if (actuel->y == 0)
                return 0;
            break;

        case 's' :
            if (actuel->y == 3)
                return 0;
            break;

        case 'd' :
            if (actuel->x == 3)
                return 0;
            break;

        case 'q' :
            if (actuel->x == 0)
                return 0;
            break;

        default :
            return 0;
    }

    return 1;
}


int deplacement(ListCase grille, char touch) {

    ListCase nouveau = grille;
    ListCase actuel = grille;
    int actuel_x, actuel_y;

    assert(grille != NULL);

    while (actuel->passe != 1) {
        actuel = actuel->suivant;
    }

    actuel_y = actuel->y;
    actuel_x = actuel->x;


    switch (touch) {
        case 'z' :
            if (deplacement_valide(touch, grille)) {

                actuel_y--;
                while (nouveau->y != actuel_y || nouveau->x != actuel_x) {
                    nouveau = nouveau->suivant;
                }

                actuel->passe = 0;
                nouveau->passe = 1;

                return 1;
            } else
                return 0;
            break;

        case 's' :
            if (deplacement_valide(touch, grille)) {

                actuel_y++;
                while (nouveau->y != actuel_y || nouveau->x != actuel_x) {
                    nouveau = nouveau->suivant;
                }
                actuel->passe = 0;
                nouveau->passe = 1;

                return 1;
            } else
                return 0;
            break;

        case 'd' :
            if (deplacement_valide(touch, grille)) {

                actuel_x++;
                while (nouveau->y != actuel_y || nouveau->x != actuel_x) {
                    nouveau = nouveau->suivant;
                }
                actuel->passe = 0;
                nouveau->passe = 1;

                return 1;
            } else
                return 0;
            break;

        case 'q' :
            if (deplacement_valide(touch, grille)) {

                actuel_x--;
                while (nouveau->y != actuel_y || nouveau->x != actuel_x) {
                    nouveau = nouveau->suivant;
                }
                actuel->passe = 0;
                nouveau->passe = 1;

                return 1;
            } else
                return 0;
            break;

        default :
            return 0;
    }


}


Lettre init_mot() {
    Lettre mot;

    mot.lettre = '.';
    mot.suivant = NULL;

    return mot;
}


int alloue_lettre(Mot mot, char lettre, int y, int x) {

    Mot m = (Mot) malloc(sizeof(Lettre));
    Mot actuel = mot;

    if (NULL == m)
        return 0;

    while (actuel->suivant != NULL) {
        actuel = actuel->suivant;
    }

    m->lettre = (char) tolower(lettre);
    m->y = y;
    m->x = x;
    m->suivant = NULL;
    actuel->suivant = m;

    return 1;
}


int ajoute_lettre_valide(ListCase grille, Mot mot) {

    ListCase actuel = grille;
    ListCase voisin = grille;
    assert(NULL != grille);

    if (NULL != mot->suivant) {

        while (actuel->passe != 1) {
            actuel = actuel->suivant;
        }

        while (NULL != voisin) {

            if (voisin->x == actuel->x - 1 && voisin->y == actuel->y - 1) {
                if (voisin->valide == 1 && actuel->valide == 0)
                    return 1;
            } else if (voisin->x == actuel->x && voisin->y == actuel->y - 1) {
                if (voisin->valide == 1 && actuel->valide == 0)
                    return 1;
            } else if (voisin->x == actuel->x + 1 && voisin->y == actuel->y - 1) {
                if (voisin->valide == 1 && actuel->valide == 0)
                    return 1;
            } else if (voisin->x == actuel->x + 1 && voisin->y == actuel->y) {
                if (voisin->valide == 1 && actuel->valide == 0)
                    return 1;
            } else if (voisin->x == actuel->x + 1 && voisin->y == actuel->y + 1) {
                if (voisin->valide == 1 && actuel->valide == 0)
                    return 1;
            } else if (voisin->x == actuel->x && voisin->y == actuel->y + 1) {
                if (voisin->valide == 1 && actuel->valide == 0)
                    return 1;
            } else if (voisin->x == actuel->x - 1 && voisin->y == actuel->y + 1) {
                if (voisin->valide == 1 && actuel->valide == 0)
                    return 1;
            } else if (voisin->x == actuel->x - 1 && voisin->y == actuel->y) {
                if (voisin->valide == 1 && actuel->valide == 0)
                    return 1;
            }

            voisin = voisin->suivant;
        }

        return 0;
    }

    return 1;

}


int ajoute_lettre(ListCase grille, Mot mot) {

    ListCase actuel = grille;

    while (actuel->passe != 1) {
        actuel = actuel->suivant;
    }

    actuel->valide = 1;
    alloue_lettre(mot, actuel->lettre, actuel->y, actuel->x);

    return 1;
}


int suppressionFin(Mot mot, ListCase grille) {

    assert(mot != NULL);

    Mot aSupprimer = mot;
    ListCase actuel = grille;

    while (NULL != aSupprimer->suivant->suivant) {
        aSupprimer = aSupprimer->suivant;
    }

    while (actuel->y != aSupprimer->suivant->y || actuel->x != aSupprimer->suivant->x) {
        actuel = actuel->suivant;
    }

    actuel->valide = 0;
    free(aSupprimer->suivant);
    aSupprimer->suivant = NULL;

    return 1;
}


int nb_lettre(Mot mot) {

    Mot lettre = mot->suivant;
    int nb_lettre = 1;


    assert(NULL != mot->suivant);

    while (lettre != NULL) {
        nb_lettre++;
        lettre = lettre->suivant;
    }

    return nb_lettre;

}


void mot_entrer(Mot mot, char *mot_final) {

    Mot lettre = mot->suivant;
    int i = 0;

    assert(NULL != mot->suivant);
    assert(NULL != mot_final);

    while (lettre != NULL) {

        mot_final[i] = lettre->lettre;
        i++;
        lettre = lettre->suivant;
    }

    return;
}


void destructListe(Mot mot, ListCase grille) {

    assert(NULL != mot->suivant);

    while (mot->suivant != NULL) {
        suppressionFin(mot, grille);
    }

    return;
}

float puissance(float x, int n) {
    if (n == 0)
        return 1;

    else
        return x * puissance(x, n - 1);
}


int scoreOneWord(char *word) {
    assert(strlen(word) >= 3);

    return puissance(2, (strlen(word) - 3));
}

