#ifndef __CASE_H
#define __CASE_H

#include <stdio.h>
#include <stdlib.h>


typedef struct __s_cell {
    int x, y;
} Cell;

Cell create_cell(int x, int y);

void display_cell(Cell cell);

int equals_cells(Cell cell1, Cell cell2);

#endif /* __CASE_H */
