#include "Graphe.h"

#define TAILLE 16


int main(void) {
    FILE *fichier;
    Case grille;
    Lettre mot;
    Tarbre a = NULL;
    char touch;
    int sort = 0;
    char *mot_final = (char *) malloc(sizeof(char) * 2);
    int taille_mot;
    int nombre_tentatives = 0;
    int score = 0;

    srand(time(NULL));

    fichier = fopen("Mots", "r");
    if (!fichier) return 1;
    lireFichier(fichier, &a);

    grille = init_grille();
    mot = init_mot();
    rempli_grille(&grille);

    initscr();
    curs_set(0);
    noecho();
    affiche_lettre(&grille);

    while (nombre_tentatives != 4) {

        touch = getch();

        switch (touch) {
            case 'z':
            case 's':
            case 'q':
            case 'd':
                deplacement(&grille, touch);
                break;
            case ' ':
                if (ajoute_lettre_valide(&grille, &mot))
                    ajoute_lettre(&grille, &mot);
                break;
            case 'a':
                if (NULL != mot.suivant)
                    suppressionFin(&mot, &grille);
                break;
            case '\n':
                if (NULL != mot.suivant) {
                    nombre_tentatives++;
                    taille_mot = nb_lettre(&mot);
                    mot_final = (char *) realloc(mot_final, sizeof(char) * taille_mot);
                    mot_entrer(&mot, mot_final);
                    if (recherche(a, mot_final)) {
                        score += scoreOneWord(mot_final);
                    }
                    destructListe(&mot, &grille);

                }
                break;
            case 'x':
                sort = 1;
            default:
                break;

        }

        if (sort)
            break;
        clear();
        affiche_lettre(&grille);
        affiche_mot_ncurs(&mot);
    }

    if (!sort) getch();
    endwin();

    printf("Score : %d\n", score);

    return 0;
}
