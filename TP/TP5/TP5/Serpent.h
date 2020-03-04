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
typedef struct cellule_serpent{
    
    Case case_serpent;
    struct cellule *suivant;
    
}CelluleSerpent , *ListeSerpent;


typedef struct serpent{
    
    Direction direction;
    ListeSerpent corps;
    
}Serpent;


#endif /* Serpent_h */
