//
//  Triangle.c
//  
//
//  Created by Chayma guerrassi on 06/02/2020.
//

#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>
#include <unistd.h>


void triangle1(int n, char* c){
    /*Fonction qui dessine un triangle de caractère c, de base 2n+1 et de hauteur n+1 pointant vers le bas */
    
   
        int i, j;

        for (i=0 ; i < n/2+1 ; i++) {
            for (j=0 ; j < n ; j++)
                printf("%s",i <= j && i <= -j+n-1? c : " ");
            printf("\n");
        }
}




 int main(void) {
     
     triangle1(7, "*");
 }

