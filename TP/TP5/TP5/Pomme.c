//
//  Pomme.c
//  TP5
//


#include "Pomme.h"

Pomme pomme_gen_alea(int n, int m){
    
    Pomme new_pomme;
        
    new_pomme.case_pomme.y = rand() % n;
    new_pomme.case_pomme.x = rand() % m;
    
    return new_pomme;
    
}
