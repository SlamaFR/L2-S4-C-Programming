#include <ncurses.h>
#include <sys/time.h>
#include <unistd.h>
#include <assert.h>

#define MAX_TIME 359999999
#define N 7

typedef struct timeval Time;

typedef struct Chrono {
    int etat;
    long duree_totale;
    long minuteur;
    long tours[N];
    int nb_tours;
    int indice_tour;
} Chronometre;

Chronometre initialiser_chronometre() {
    Chronometre chrono;
    chrono.etat = 0;
    chrono.nb_tours = 0;
    chrono.duree_totale = 0;
    chrono.minuteur = 25 * 1000;
    return chrono;
}

int intervalle_ms(Time debut, Time fin) {
    return (fin.tv_sec - debut.tv_sec) * 1000 + (fin.tv_usec - debut.tv_usec) / 1000;
}

int nb_ms_vers_centiemes(int nb_ms) {
    return (nb_ms / 10) % 100;
}

int nb_ms_vers_secondes(int nb_ms) {
    return (nb_ms / 1000) % 60;
}

int nb_ms_vers_minutes(int nb_ms) {
    return (nb_ms / (60 * 1000)) % 60;
}

int nb_ms_vers_heures(int nb_ms) {
    return (nb_ms / (60 * 1000)) / 60;
}

void ajouter_tour(Chronometre *chrono) {
    assert(chrono != NULL);
    assert(chrono->tours != NULL);
    int i;

    for (i = chrono->indice_tour; i > 0; i--)
        chrono->tours[i] = chrono->tours[i - 1];

    chrono->tours[0] = chrono->duree_totale;

    if (chrono->indice_tour < N - 1)
        chrono->indice_tour++;

    chrono->nb_tours++;
}

void afficher_duree(int y, int x, int duree) {
    mvprintw(y, x, "%02d : %02d : %02d : %02d",
             nb_ms_vers_heures(duree),
             nb_ms_vers_minutes(duree),
             nb_ms_vers_secondes(duree),
             nb_ms_vers_centiemes(duree));
}

void afficher_interface(Chronometre chrono) {
    int i, j;

    for (i = 0; i < LINES - 10; i++)
        for (j = 0; j < COLS; j++)
            mvaddch(i, j, ' ');

    mvprintw(0, COLS / 2 - 8, "== Chronometre ==");

    for (i = 0; i < LINES - 11 && i < chrono.indice_tour && chrono.indice_tour != 0; i++) {
        mvprintw(LINES - 11 - i, COLS / 2 - 19, "Tour %d", chrono.nb_tours - i);
        mvprintw(LINES - 11 - i, COLS / 2 - 10, ":");
        afficher_duree(LINES - 11 - i, COLS / 2 - 8, chrono.tours[i]);
    }


    afficher_duree(LINES - 10, COLS / 2 - 8, chrono.duree_totale);
    mvprintw(LINES - 9, COLS / 2 - 24, "Avertissement :");
    afficher_duree(LINES - 9, COLS / 2 - 8, chrono.minuteur);
    for (i = 0; i < COLS; i++)
        mvaddch(LINES - 8, i, '-');
    mvprintw(LINES - 7, 0, "Espace : lancer / mettre en pause");
    mvprintw(LINES - 6, 0, "r      : reinitialiser");
    mvprintw(LINES - 5, 0, "t      : marquer un tour");
    mvprintw(LINES - 4, 0, "F1/F2  : incrementer / decrementer heure avertissement");
    mvprintw(LINES - 3, 0, "F3/F4  : incrementer / decrementer minute avertissement");
    mvprintw(LINES - 2, 0, "F5/F6  : incrementer / decrementer seconde avertissement");
    mvprintw(LINES - 1, 0, "q      : quitter");
    refresh();
}

int main(void) {
    Time temps_debut, temps_fin;
    int touche, alarme = 0;
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);

    Chronometre chrono = initialiser_chronometre();
    gettimeofday(&temps_debut, NULL);
    gettimeofday(&temps_fin, NULL);

    afficher_interface(chrono);
    while (1) {
        touche = getch();

        if (COLS < 58 || LINES < 14) {
            clear();
            attron(A_BOLD);
            mvprintw(0, 0, "ERREUR : ");
            attroff(A_BOLD);
            printw("Taille de la fenêtre trop petite !");
            continue;
        }

        if (touche != ERR) {
            if (touche == ' ') {
                chrono.etat = !chrono.etat;
            } else if (touche == 'q') {
                break;
            } else if (touche == 'r') {
                chrono.duree_totale = 0;
                chrono.indice_tour = 0;
                chrono.etat = 0;
                alarme = 0;
            } else if (touche == 't') {
                ajouter_tour(&chrono);
            } else {
                switch (touche) {
                    case KEY_F(1):
                        if (chrono.minuteur + 60 * 60 * 1000 > 359999000)
                            break;
                        chrono.minuteur += 60 * 60 * 1000;
                        break;
                    case KEY_F(2):
                        if (chrono.minuteur < 60 * 60 * 1000)
                            break;
                        chrono.minuteur -= 60 * 60 * 1000;
                        break;
                    case KEY_F(3):
                        if (chrono.minuteur + 60 * 1000 > 359999000)
                            break;
                        chrono.minuteur += 60 * 1000;
                        break;
                    case KEY_F(4):
                        if (chrono.minuteur < 60 * 1000)
                            break;
                        chrono.minuteur -= 60 * 1000;
                        break;
                    case KEY_F(5):
                        if (chrono.minuteur + 1000 > 359999000)
                            break;
                        chrono.minuteur += 1000;
                        break;
                    case KEY_F(6):
                        if (chrono.minuteur <= 1000)
                            break;
                        chrono.minuteur -= 1000;
                        break;
                    case KEY_RESIZE:
                        clear();
                        afficher_interface(chrono);
                        refresh();
                        break;
                    default:
                        continue;
                }
            }
        }

        usleep(5000);

        if (chrono.etat == 0) {
            gettimeofday(&temps_debut, NULL);
            afficher_interface(chrono);
            refresh();
            continue;
        }

        gettimeofday(&temps_fin, NULL);
        chrono.duree_totale += intervalle_ms(temps_debut, temps_fin);

        if (chrono.duree_totale > MAX_TIME)
            chrono.duree_totale = 0;

        temps_debut = temps_fin;

        if (chrono.minuteur < chrono.duree_totale && alarme == 0) {
            flash();
            alarme = 1;
        }

        afficher_interface(chrono);
    }

    endwin();
    return 0;
}
