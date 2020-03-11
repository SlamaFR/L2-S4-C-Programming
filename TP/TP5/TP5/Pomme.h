#ifndef __POMME_H
#define __POMME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Case.h"

typedef struct __s_apple {
    Cell apple_cell;
} Apple;

Apple generate_random_apple(int n, int m);

#endif /* __POMME_H */
