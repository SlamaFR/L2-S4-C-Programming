#ifndef __MONDE_H
#define __MONDE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Pomme.h"
#include "Serpent.h"
#include "Case.h"
#include "Direction.h"

typedef struct __s_appleCell {
    Apple apple;
    struct __s_appleCell *next;
} AppleCell, *AppleList;

typedef struct __s_world {
    int height, width;
    int eaten_apple_amount;
    AppleList apples;
    Snake snake;
} World;

int empty_cell(World world, Cell cell);

int snake_in_cell(World world, Cell cell);

int cell_in_world(World world, Cell cell);

Cell next_cell(Cell cell, Direction direction);

int move_snake(World *world);

int eat_apple(World *world);

int snake_death(World *world);

int add_apple_to_world(World *world);

World init_world(int apples_amount);

Snake init_snake(World world);

#endif /* Monde_h */
