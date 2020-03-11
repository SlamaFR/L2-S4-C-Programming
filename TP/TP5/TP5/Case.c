#include <stdio.h>
#include "Case.h"

Cell create_cell(int x, int y) {
    Cell cell;
    cell.x = x;
    cell.y = y;
    return cell;
}

void display_cell(Cell cell) {
    printf("{cell|x=%d;y=%d}\n", cell.x, cell.y);
}

int equals_cells(Cell cell1, Cell cell2) {
    return cell1.x == cell2.x && cell1.y == cell2.y;
}
