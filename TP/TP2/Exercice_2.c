#include <stdio.h>
#include <string.h>

int main(void) {
    char *s1 = "arbre";

    printf("strchr(\"%s\", \'r\') = %s\n", s1, strchr(s1, 'r'));
    printf("strrchr(\"%s\", \'r\') = %s\n", s1, strrchr(s1, 'r'));
    return 0;
}