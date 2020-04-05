#ifndef __REGLE__
#define __REGLE__
#include "Dictionnaire.h"



typedef struct mot {
    char lettre;
    int y;
    int x;
    struct mot *suivant;
} Lettre, *Mot;

int deplacement_valide(char touch, ListCase grille);

int deplacement(ListCase grille, char touch);

Lettre init_mot();

int alloue_lettre(Mot mot, char lettre, int y, int x);

int ajoute_lettre_valide(ListCase grille, Mot mot);

int ajoute_lettre(ListCase grille, Mot mot);

void affiche_mot(const Mot mot);

int suppressionFin(Mot mot, ListCase grille);

int nb_lettre(Mot mot);

void mot_entrer(Mot mot, char* mot_final);

void destructListe(Mot mot, ListCase grille);

float puissance(float x, int n);

int scoreOneWord(char *word);


#endif
