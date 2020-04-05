#ifndef __TEST__
#define __TEST__
#include "Grille.h"
#include "Graphe.h"
#include "Dictionnaire.h"
#include "Regles.h"

int test_alloueNoeud(char lettre);

int test_recherche(Tarbre a, char *m);

int test_nombre_mots(Tarbre a);

int test_ajoute_mot(Tarbre* a, char *m);

int test_lireFichier(FILE *file, Tarbre *a);

int test_init_grille();

int test_alloue_case(ListCase grille, char lettre);

int test_gen_aleatoire();

int test_rempli_grille(ListCase grille);

int test_deplacement_valide(char touch, ListCase grille);

int test_deplacement(ListCase grille, char touch);

int test_init_mot();

int test_alloue_lettre(Mot mot, char lettre, int y, int x);

int test_ajoute_lettre_valide(ListCase grille, Mot mot);

int test_ajoute_lettre(ListCase grille, Mot mot);

int test_suppressionFin(Mot mot, ListCase grille);

int test_mot_entrer(Mot mot, char* mot_final);

int test_destructListe(Mot mot, ListCase grille);

int test_puissance(float x, int n);

int test_scoreOneWord(char *word);


#endif
