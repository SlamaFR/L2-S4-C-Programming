//
//  Exercice2.c
//
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


typedef struct Chrono{
    int etat;
    long int duree_totale;
    long int minuteur;
    int indice_tour;
    int nb_tours;
    static int tours[20];
}Chronometre;

Chronometre initialiser_chronometre(){
    
    Chronometre chrono;
    
    chrono.etat = 0;
    chrono.indice_tour = 0;
    chrono.nb_tours = 0;
    
    return chrono;
}
