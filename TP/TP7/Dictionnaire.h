#ifndef __DICTIONNAIRE__
#define __DICTIONNAIRE__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Grille.h"

typedef struct noeud{
    char lettre;
    struct noeud *fg;
    struct noeud *fd;
    struct noeud *fils;
}Tnoeud, *Tarbre;

Tarbre alloueNoeud(char lettre);

int recherche(Tarbre a, char *m);

int ajoute_mot(Tarbre* a, char *m);

int lireFichier(FILE *file, Tarbre *a);

void affiche_mots_aux(Tarbre a, char *buffer, int indice);

void affiche_mots(Tarbre a);

#endif
