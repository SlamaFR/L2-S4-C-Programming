#ifndef __GRILLE__
#define __GRILLE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>


typedef struct cases {
    int y;
    int x;
    char lettre;
    int passe;
    int valide;
    struct cases *suivant;
} Case, *ListCase;


/*Initialise la liste chainée qui représentera la grille*/
Case init_grille();

/*Ajoute une case à grille*/
int alloue_case(ListCase grille, char lettre);

/*génère une lettre aléatoirement*/
char gen_aleatoire();

/*remplie grille de lettre généré aléatoirement*/
int rempli_grille(ListCase grille);

/**/
void affiche_grille(const ListCase grille);

#endif
