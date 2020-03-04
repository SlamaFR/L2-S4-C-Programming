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
