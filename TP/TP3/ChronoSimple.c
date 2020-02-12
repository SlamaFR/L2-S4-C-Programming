#include <sys/time.h>
#include <ncurses.h>
#include <unistd.h>

typedef struct timeval Time;

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
    return nb_ms_vers_minutes(nb_ms) / 60;
}

int main(void) {
    Time temps_debut, temps_fin;
    int temps = 0, running = 0;
    char touche;
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);

    gettimeofday(&temps_debut, NULL);
    gettimeofday(&temps_fin, NULL);

    mvprintw(5, 10, "0 : 0 : 0 : 0");

    while (1) {
        touche = getch();

        if (touche == ' ') {
            gettimeofday(&temps_debut, NULL);
            running = !running;
        }

        usleep(5000);

        if (!running)
            continue;

        gettimeofday(&temps_fin, NULL);
        temps += intervalle_ms(temps_debut, temps_fin);
        temps_debut = temps_fin;

        /* clear(); */
        mvprintw(5, 10, "%d : %d : %d : %d",
                 nb_ms_vers_heures(temps),
                 nb_ms_vers_minutes(temps),
                 nb_ms_vers_secondes(temps),
                 nb_ms_vers_centiemes(temps));
        refresh();
    }

    endwin();
    return 0;
}
