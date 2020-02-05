#include <stdio.h>
#include <string.h>

int main(void) {
    char *s1 = "arbre", *s2 = "avion";

    printf("strcmp(\"%s\", \"%s\") = %d\n", s1, s2, strcmp(s1, s2));
    printf("strcmp(\"%s\", \"%s\") = %d\n", s2, s2, strcmp(s2, s2));
    printf("strcmp(\"%s\", \"%s\") = %d\n", s2, s1, strcmp(s2, s1));
    return 0;
}