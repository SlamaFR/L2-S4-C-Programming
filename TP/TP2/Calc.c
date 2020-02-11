//
//  Calc.c
//  
//
//  Created by Chayma guerrassi on 05/02/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



int main(int argc, char *argv[]){
    
    /*Vérifie que le nombre d'arguments est supérieur ou égal à 3*/
    assert( argc >= 3);
    
    /*Vérifie que le deuxième argument saisie est bien un opérateur valide.*/
    assert( strcmp(argv[1], "+") == 0 || strcmp(argv[1], "-") == 0 || strcmp(argv[1], "x") == 0 || strcmp(argv[1], "/") == 0);
    
    
    int result;
    int op1, op2;
    
    op1 = atoi(argv[2]);
    op2 = atoi(argv[3]);
    
    if (strcmp(argv[1], "/") == 0){
        /* Dans le cas d'une division, vérifie que le dénominateur n'est pas égal à 0. */
        assert(op2 != 0);
        result = op1 / op2;
        
    }
    else if (strcmp(argv[1], "+") == 0)
        result = op1 + op2;
    
    else if (strcmp(argv[1], "-") == 0)
        result = op1 - op2;
    
    else if (strcmp(argv[1], "x") == 0)
        result = op1 * op2;
    
    printf("Résultat : %d \n", result);

}

