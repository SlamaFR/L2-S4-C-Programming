//
//  Pomme.h
//  TP5
//


#ifndef Pomme_h
#define Pomme_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Case.h"

typedef struct pomme{
    
    Case case_pomme;
}Pomme;

Pomme pomme_gen_alea(int n, int m);

#endif /* Pomme_h */
