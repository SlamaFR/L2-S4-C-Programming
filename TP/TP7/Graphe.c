#include "Graphe.h"


void affiche_lettre(ListCase grille) {

    ListCase actuel = grille;
    int i, j;

    assert(grille != NULL);

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);


    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (actuel->passe == 1) {
                attron(COLOR_PAIR(1));
                mvaddch(j + 1, i * 2, actuel->lettre);
                attroff(COLOR_PAIR(1));
            } else if (actuel->valide == 1) {
                attron(COLOR_PAIR(2));
                mvaddch(j + 1, i * 2, actuel->lettre);
                attroff(COLOR_PAIR(2));
            } else
                mvaddch(j + 1, i * 2, actuel->lettre);

            if (actuel->y != j || actuel->x != i) {
                actuel->y = j;
                actuel->x = i;
            }
            actuel = actuel->suivant;
        }
    }

    refresh();
    return;

}

void affiche_mot_ncurs(Mot mot) {

    assert(NULL != mot);

    Mot lettre = mot->suivant;
    move(6, 1);
    while (lettre != NULL) {
        addch(lettre->lettre);
        lettre = lettre->suivant;
    }

    return;
}
