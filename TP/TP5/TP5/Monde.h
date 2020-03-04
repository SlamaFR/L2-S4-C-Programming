#ifndef __MONDE_H
#define __MONDE_H

#include <stdio.h>
#include <stdlib.h>
#include "Pomme.h"
#include "Serpent.h"

typedef struct cellpomme {
    Pomme pomme;
    struct cellpomme *suivant;
} CellulePomme, *ListePomme;

typedef struct monde {
    int nombre_lignes, nombre_colonnes;
    int nombre_pommes_mangees;
    ListePomme pommes;
    Serpent serpent;
} Monde;

int case_vide(Monde monde, Case _case);

int serpent_dans_case(Monde monde, Case _case);

int case_dans_monde(Monde monde, Case _case);

Case prochaine_case(Case _case, Direction direction);

int deplacer_serpent(Monde *monde);

int manger_pomme(Monde *monde);

int mort_serpent(Monde *monde);

#endif /* __MONDE_H */
