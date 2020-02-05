#include <stdio.h>
#include <stdlib.h>

int bon_modulo(int a, int b) {
    int result = a % b;
    return result < 0 ? result + b : result;
}

char cryptchr(int key, char c) {
    if ('a' <= c && c <= 'z')
        return (char) (bon_modulo(c - 'a' + key, 26) + 'a');
    if ('A' <= c && c <= 'Z')
        return (char) (bon_modulo(c - 'A' + key, 26) + 'A');
    return c;
}

int main(int argc, char *argv[]) {
    int key, i;

    if (argc < 3)
        return EXIT_FAILURE;

    key = atoi(argv[1]);

    for (i = 2; i < argc; i++) {
        for (; *argv[i]; argv[i]++)
            printf("%c", cryptchr(key, *argv[i]));
        printf(" ");
    }
    printf("\n");

    return EXIT_SUCCESS;
}