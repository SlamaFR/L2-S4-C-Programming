#include <sys/time.h>
#include <stdio.h>

typedef struct timeval Time;

int nb_ms_vers_centiemes(int nb_ms);
int nb_ms_vers_secondes(int nb_ms);
int nb_ms_vers_minutes(int nb_ms);
int nb_ms_vers_heures(int nb_ms);

int main(int argc, const char * argv[]) {
    int cent = nb_ms_vers_centiemes(1213);
    printf("cent = %d", cent);
}

int intervalle_ms(Time debut, Time fin) {
    return (fin.tv_sec - debut.tv_sec) * 1000 + (fin.tv_usec - debut.tv_usec) / 1000;
}

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

