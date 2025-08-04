#include <string.h>
#include <stdio.h>
#include <stdlib.h>





//GLIDER PATTERN:
void populate_with_glider(int *array, int rows, int columns, int start_row, int start_col) {
    // 1. First, clear the entire board by setting all cells to 0 (dead).
    memset(array, 0, rows * columns * sizeof(int));

    // 2. Check if the glider can fit without going out of bounds.
    // The pattern is 3x3, so we need at least 3 cells of space.
    if (start_row + 2 >= rows || start_col + 2 >= columns) {
        printf("Warning: Glider starting position is too close to the edge. Board is empty.\n");
        return;
    }

    // 3. Define the 5 live cells of the Glider pattern relative to the start position.
    // The pattern looks like this:
    //   . X .
    //   . . X
    //   X X X
    // Where 'X' is a live cell (1) and '.' is a dead cell (0).

    array[(start_row + 0) * columns + (start_col + 1)] = 1; // Top middle
    array[(start_row + 1) * columns + (start_col + 2)] = 1; // Middle right
    array[(start_row + 2) * columns + (start_col + 0)] = 1; // Bottom left
    array[(start_row + 2) * columns + (start_col + 1)] = 1; // Bottom middle
    array[(start_row + 2) * columns + (start_col + 2)] = 1; // Bottom right
}





//RANDOM PATTERN: populates the cells with either 1 or 0 randomly
void populate_array_randomly(int *array, int rows, int columns) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j <columns; j++) {
            array[i*columns + j] = rand() % 2;
        }
    }
}
