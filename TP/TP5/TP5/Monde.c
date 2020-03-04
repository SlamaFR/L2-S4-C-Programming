#include "Monde.h"
#include "Serpent.h"
#include <assert.h>

int case_vide(Monde monde, Case _case) {
    CellulePomme *pomme;
    for (pomme = monde.pommes; pomme != NULL; pomme = pomme->suivant) {
        if (_case.x != pomme->pomme.case_pomme.x)
            continue;
        if (_case.y != pomme->pomme.case_pomme.y)
            continue;
        return 0;
    }
    return 1;
}

int serpent_dans_case(Monde monde, Case _case) {
    CelluleSerpent *serpent;
    for (serpent = monde.serpent.corps; serpent != NULL; serpent = serpent->suivant) {
        if (_case.x != serpent->case_serpent.x)
            continue;
        if (_case.y != serpent->case_serpent.y)
            continue;
        return 1;
    }
    return 0;
}

int case_dans_monde(Monde monde, Case _case) {
    if (_case.x < 0 || _case.x >= monde.nombre_colonnes)
        return 0;
    if (_case.y < 0 || _case.y >= monde.nombre_lignes)
        return 0;
    return 1;
}

Case prochaine_case(Case _case, Direction direction) {
    Case prochaine_case;
    switch (direction) {
        case SUD:
            prochaine_case.x = _case.x;
            prochaine_case.y = _case.y + 1;
            break;
        case NORD:
            prochaine_case.x = _case.x;
            prochaine_case.y = _case.y - 1;
            break;
        case EST:
            prochaine_case.x = _case.x + 1;
            prochaine_case.y = _case.y;
            break;
        case OUEST:
            prochaine_case.x = _case.x - 1;
            prochaine_case.y = _case.y;
            break;
        default:
            return _case;
    }
    return prochaine_case;
}

int deplacer_serpent(Monde *monde) {
    assert(monde != NULL);
    assert(monde->serpent.corps != NULL);

    Case _case = prochaine_case(monde->serpent.corps->case_serpent, monde->serpent.direction);
    if (!case_vide(*monde, _case) || !case_dans_monde(*monde, _case) || serpent_dans_case(*monde, _case))
        return 0;

    inserer_tete(&monde->serpent.corps, _case);
    supprimer_queue(&monde->serpent.corps);
    return 1;
}

int manger_pomme(Monde *monde) {
    assert(monde != NULL);
    assert(monde->serpent.corps != NULL);

    Case _case = prochaine_case(monde->serpent.corps->case_serpent, monde->serpent.direction);
    if (case_vide(*monde, _case) || !case_dans_monde(*monde, _case) || serpent_dans_case(*monde, _case))
        return 0;

    inserer_tete(&monde->serpent.corps, _case);
    return 1;
}

int mort_serpent(Monde *monde) {
    assert(monde != NULL);
    assert(monde->serpent.corps != NULL);

    Case _case = prochaine_case(monde->serpent.corps->case_serpent, monde->serpent.direction);
    return (!case_dans_monde(*monde, _case) || serpent_dans_case(*monde, _case));
}


Serpent init_serpent(Monde mon){
    
    Serpent serpent;
    
    serpent.direction = EST;
    serpent.corps = malloc(sizeof(CelluleSerpent));
    
    if(serpent.corps != NULL){
        serpent.corps->case_serpent.y = mon.nombre_lignes/2;
        serpent.corps->case_serpent.x = mon.nombre_colonnes/2;
        serpent.corps->suivant = NULL;
    }

    
    /*Première case après la tête*/
    serpent.corps->suivant->case_serpent.y = serpent.corps->case_serpent.y;
    serpent.corps->suivant->case_serpent.x = serpent.corps->case_serpent.x-1;
    
    /*Deuxième case après la tête*/
    serpent.corps->suivant->suivant->case_serpent.y = serpent.corps->suivant->case_serpent.y;
    serpent.corps->suivant->suivant->case_serpent.x = serpent.corps->suivant->case_serpent.x-1;
    
    /*Troisième case après la tête*/
    serpent.corps->suivant->suivant->suivant->case_serpent.y = serpent.corps->suivant->suivant->case_serpent.y;
    serpent.corps->suivant->suivant->suivant->case_serpent.x = serpent.corps->suivant->suivant->case_serpent.x-1;
    
    serpent.corps->suivant->suivant->suivant->suivant = NULL;
    
    return serpent;
}
void ajouter_pomme_monde(Monde *mon){
    
    mon->pommes = malloc(sizeof(CellulePomme));
    if (case_vide){
        
    }
    
    
}
Monde init_monde(int nb_pommes){
    
    Monde monde;
    int i;
    
    monde.nombre_colonnes = 64;
    monde.nombre_lignes = 32;
    monde.nombre_pommes_mangees = 0;
    
    monde.pommes = malloc(sizeof(CellulePomme));
    
    if(monde.pommes != NULL){
        i=0;
        ListePomme actuel = monde.pommes;
        
        while (i < nb_pommes){
            actuel->pomme = pomme_gen_alea(monde.nombre_lignes, monde.nombre_colonnes);
            actuel = actuel->suivant;
        }
        
        actuel->suivant = NULL;
    }
    
    monde.serpent = init_serpent(monde);
    
    return monde;
}
