//
//  main.c
//  TP5
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DET

int main(int argc, const char * argv[]) {
    
#ifdef DET
    srand(0);
#else
    srand(time(NULL));
    
    
    
    return 0;
#endif
}
