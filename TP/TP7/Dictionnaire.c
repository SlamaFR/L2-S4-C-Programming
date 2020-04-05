#include "Dictionnaire.h"
#include <ctype.h>
#define MAX 30

Tarbre alloueNoeud(char lettre) {
    Tarbre nouveau = malloc(sizeof(Tnoeud));
    
    if (nouveau == NULL) {
        fprintf(stderr, "allocation impossible");
        exit(1);
    }
    nouveau->lettre = lettre;
    nouveau->fg = nouveau->fd = nouveau->fils = NULL;
    return nouveau;
}


int recherche(Tarbre a, char *m){
    if(a==NULL)
        return 0;

    if(a->lettre == *m){
        if (a->lettre == '\0')
            return 1;
    
        return recherche(a->fils, m+1);
    }
    if(a->lettre < *m)
        return recherche(a->fd, m);

    return recherche(a->fg, m);
    
}

int ajoute_mot(Tarbre* a, char *m){
    if((*a)==NULL)
        (*a) = alloueNoeud(*m);
    if((*a)==NULL)
        return 0;

    if((*a)->lettre == '\0' && *m=='\0')
        return 1;

    if((*a)->lettre == *m)
        return ajoute_mot(&((*a)->fils), m+1);

    if((*a)->lettre > *m)
        return ajoute_mot(&((*a)->fg), m);

    return ajoute_mot(&((*a)->fd), m);
    
}

int lireFichier(FILE *file, Tarbre *a) {
    int charPos = 0, posMotActuel = 0, ascii = 0;
    char *mot = NULL, *tmp = NULL, actuel = 0;
    size_t taille = 0;
    

    mot = (char *) malloc(0);
    if (!mot)
        return 0;

    while ((actuel = (char) fgetc(file)) && actuel != EOF) {
        if (actuel != ' ' && actuel != '\n' && actuel != '\t' && actuel != '.' && actuel != ';' &&
            actuel != ',' && actuel != '?' && actuel != '!') {

            taille++;
            tmp = (char *) realloc(mot, taille + 2);
            if (!tmp) {
                free(mot);
                return 0;
            }
            mot = tmp;
            mot[charPos - posMotActuel] = (char) tolower(actuel);
        } else {
            if (mot) {
                mot[charPos - posMotActuel] = '\0';
                ajoute_mot(a, mot);
                free(mot);
                mot = NULL;
            }
            posMotActuel = charPos + 1;
            taille = 0;
        }
        charPos++;
    }
    return 1;
}


void affiche_mots_aux(Tarbre a, char *buffer, int indice) {
    if(a==NULL)
        return;

    affiche_mots_aux(a->fg, buffer, indice);
    buffer[indice] = a->lettre;
    
    /* Si on arrive à une fin de mot, on affiche
    le buffer courant. */
    if (a->lettre == '\0'){
        printf("%s",buffer );
        printf("\n");
    } else {
        affiche_mots_aux(a->fils, buffer, indice+1);
    }
    
    affiche_mots_aux(a->fd, buffer, indice);
}


void affiche_mots(Tarbre a) {
    char buffer[MAX];
    affiche_mots_aux(a,buffer,0);
}
