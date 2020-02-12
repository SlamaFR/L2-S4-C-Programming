#include <sys/time.h>
#include <ncurses.h>
#include <unistd.h>

int nb_ms_vers_centiemes(int nb_ms){
    return (nb_ms/10)%100;
}


int nb_ms_vers_secondes(int nb_ms){
    return (nb_ms/1000)%60;
}

int nb_ms_vers_minutes(int nb_ms){
    return (nb_ms/(60*1000))%60;
}

int nb_ms_vers_heures(int nb_ms){
    return nb_ms_vers_minutes(nb_ms)/60;
}

int main(void) {
    int temps = 0;
    initscr();
    noecho();
    curs_set(0);

    while (1) {
        clear();
        mvprintw(5, 10, "%d : %d : %d : %d",
                nb_ms_vers_heures(temps),
                nb_ms_vers_minutes(temps),
                nb_ms_vers_secondes(temps),
                nb_ms_vers_centiemes(temps));
        refresh();
        usleep(500000);
        temps += 500;
    }

    endwin();
    return 0;
}
