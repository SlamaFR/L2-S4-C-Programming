//
//  Exercice2.c
//
//

#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "fonctionsTime.c"

#define N 50

typedef struct timeval Time;

typedef struct Chrono{
    int etat;
    long int duree_totale;
    long int minuteur;
    int indice_tour;
    int nb_tours;
    int tours[N];
} Chronometre;

Chronometre initialiser_chronometre(){
    
    Chronometre chrono;
    
    chrono.etat = 0;
    chrono.indice_tour = 0;
    chrono.nb_tours = 0;
    chrono.minuteur = 25 * 1000;
    
    return chrono;
}

void affiche_duree(int y, int x, int nb_ms){
    
    mvprintw(y, x, "%2d : %2d : %2d : %2d",
                nb_ms_vers_heures(nb_ms),
                nb_ms_vers_minutes(nb_ms),
                nb_ms_vers_secondes(nb_ms),
                nb_ms_vers_centiemes(nb_ms));
}

void DecaleD(int *tab){
    
    int i;
    
    for(i=0; i<N; i++)
        tab[i] = tab[i+1];
    
}

void affiche_interface(Chronometre chrono) {
    
    int i, j;
    mvprintw(0, COLS / 2 - 8, "== Chronometre ==");
    for (i = 0; i < COLS; i++)
        mvaddch(6, i, '-');

    for (i = 1; i < 6; i++)
        for (j = 0; j < COLS; j++)
            mvaddch(i, j, ' ');

    for (i = 0; i < chrono.nb_tours && i < 3; i++)
        affiche_duree(3 - i, COLS / 2 - 8, chrono.tours[i]);
    affiche_duree(4, COLS / 2 - 8, chrono.duree_totale);
    mvprintw(5, COLS / 2 - 24, "Avertissement :");
    affiche_duree(5, COLS / 2 - 8, chrono.minuteur);

    mvprintw(7, 0, "Espace : lancer / mettre en pause");
    mvprintw(8, 0, "r      : reinitialiser");
    mvprintw(9, 0, "t      : marquer un tour");
    mvprintw(10, 0, "F1/F2  : incrementer / decrementer heure avertissement");
    mvprintw(11, 0, "F3/F4  : incrementer / decrementer minute avertissement");
    mvprintw(12, 0, "F5/F6  : incrementer / decrementer seconde avertissement");
    mvprintw(13, 0, "q      : quitter (%d)", chrono.etat);
    
}

void ajouter_tour(Chronometre *chrono){
    
    /*Incrémenter l'indice du dernier tour.*/
    chrono->indice_tour++;
    
    /*Décaler le tableau vers la droite*/
    if (chrono->nb_tours >= N)
        DecaleD(chrono->tours);
    
    chrono->tours[0] = chrono->duree_totale;
}

int main(void){
    Time temps_debut, temps_fin;
    int touche;
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);

    Chronometre chrono = initialiser_chronometre();
    gettimeofday(&temps_debut, NULL);
    gettimeofday(&temps_fin, NULL);

    affiche_interface(chrono);
    while (1) {
        touche = getch();

        if (COLS < 58 || LINES < 14) {
            endwin();
            printf("ERREUR : taille de la fenêtre trop petite !\n");
            return 1;
        }

        if (touche != ERR) {
            if (touche == ' ') {
                chrono.etat = !chrono.etat;
            } else if (touche == 'q') {
                break;
            } else if (touche == 'r') {
                chrono.duree_totale = 0;
                chrono.etat = 0;
                chrono.nb_tours = 0;
            } else if (touche == 't') {
                //TODO: ajouter tour.
            } else {
                switch (touche) {
                    case KEY_F(1):
                        chrono.minuteur += 60 * 60 * 1000;
                        break;
                    case KEY_F(2):
                        if (chrono.minuteur < 60 * 60 * 1000)
                            break;
                        chrono.minuteur -= 60 * 60 * 1000;
                        break;
                    case KEY_F(3):
                        chrono.minuteur += 60 * 1000;
                        break;
                    case KEY_F(4):
                        if (chrono.minuteur < 60 * 1000)
                            break;
                        chrono.minuteur -= 60 * 1000;
                        break;
                    case KEY_F(5):
                        chrono.minuteur += 1000;
                        break;
                    case KEY_F(6):
                        if (chrono.minuteur <= 1000)
                            break;
                        chrono.minuteur -= 1000;
                        break;
                    default:
                        continue;
                }
            }
            affiche_interface(chrono);
        }

        usleep(5000);

        if (chrono.etat == 0) {
            gettimeofday(&temps_debut, NULL);
            continue;
        }

        gettimeofday(&temps_fin, NULL);
        chrono.duree_totale += intervalle_ms(temps_debut, temps_fin);
        temps_debut = temps_fin;

        if (chrono.minuteur >= chrono.duree_totale) {
//            afficher_flash();
        }

        affiche_interface(chrono);
    }

    endwin();
    return 0;
    
}
