#include <stdlib.h>
#include "Pomme.h"

Apple generate_random_apple(int n, int m) {
    Apple apple;
    apple.apple_cell.y = rand() % n;
    apple.apple_cell.x = rand() % m;
    return apple;
}
