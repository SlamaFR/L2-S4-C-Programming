#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *s1 = "10", *s2 = "arbre", *s3 = "42", *s4 = "10 avions";

    printf("atoi(\"%s\") = %d\n", s1, atoi(s1));
    printf("atoi(\"%s\") = %d\n", s2, atoi(s2));
    printf("atoi(\"%s\") = %d\n", s3, atoi(s3));
    printf("atoi(\"%s\") = %d\n", s4, atoi(s4));
    return 0;
}