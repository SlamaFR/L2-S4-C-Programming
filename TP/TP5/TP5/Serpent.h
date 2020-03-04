//
//  Serpent.h
//  TP5
//


#ifndef Serpent_h
#define Serpent_h

#include <stdio.h>
#include <stdlib.h>
#include "Direction.h"
#include "Case.h"

/* Déclaration de liste chainée représentant le serpent*/
typedef struct cellule_serpent {
    Case case_serpent;
    struct cellule_serpent *suivant;
} CelluleSerpent, *ListeSerpent;


typedef struct serpent {
    Direction direction;
    ListeSerpent corps;
} Serpent;

int inserer_tete(ListeSerpent *liste, Case _case);

int supprimer_queue(ListeSerpent *liste);

#endif /* Serpent_h */
