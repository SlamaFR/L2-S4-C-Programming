//
//  Monde.h
//  TP5
//


#ifndef Monde_h
#define Monde_h

#include <stdio.h>
#include <stdlib.h>
#include "Pomme.h"
#include "Serpent.h"

typedef struct cellpomme{
    
    Pomme pomme;
    struct cellpomme *suivant;
    
} CellulePomme, *ListePomme;

typedef struct monde{
    
    int nombre_lignes, nombre_colonnes;
    int nombre_pommes_mangees;
    ListePomme pommes;
    Serpent serpent;
    
}Monde;

#endif /* Monde_h */
