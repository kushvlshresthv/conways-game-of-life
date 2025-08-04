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




//OSCILLATORS:


void populate_with_all_oscillators(int *array, int rows, int columns) {
    // 1. First, clear the entire board.
    memset(array, 0, rows * columns * sizeof(int));

    // 2. Check if the grid is large enough for our spacious layout.
    const int MIN_ROWS = 70;
    const int MIN_COLS = 120;
    if (rows < MIN_ROWS || columns < MIN_COLS) {
        printf("Warning: Grid is too small for the spaced-out layout. A %dx%d grid is recommended.\n", MIN_COLS, MIN_ROWS);
    }

    // Helper macro to make setting cells by absolute coordinates cleaner.
    #define SET_CELL(r, c) array[(r) * columns + (c)] = 1

    // --- Pattern 1: Pulsar (13x13) ---
    // Placed in the center of the 120x70 grid.
    int pr = 28, pc = 53; // Pulsar start row and column (center)
    int offsets[] = {0, 5, 7, 12};
    // Horizontal bars
    for (int i = 0; i < 4; i++) {
        int r = pr + offsets[i];
        SET_CELL(r, pc + 2); SET_CELL(r, pc + 3); SET_CELL(r, pc + 4);
        SET_CELL(r, pc + 8); SET_CELL(r, pc + 9); SET_CELL(r, pc + 10);
    }
    // Vertical bars
    for (int i = 0; i < 4; i++) {
        int c = pc + offsets[i];
        SET_CELL(pr + 2, c); SET_CELL(pr + 3, c); SET_CELL(pr + 4, c);
        SET_CELL(pr + 8, c); SET_CELL(pr + 9, c); SET_CELL(pr + 10, c);
    }


    // --- Pattern 2: Beacon (4x4) ---
    // Placed in the top-left corner.
    int br = 10, bc = 10; // Beacon start row and column
    SET_CELL(br, bc); SET_CELL(br, bc + 1);
    SET_CELL(br + 1, bc); SET_CELL(br + 1, bc + 1);
    SET_CELL(br + 2, bc + 2); SET_CELL(br + 2, bc + 3);
    SET_CELL(br + 3, bc + 2); SET_CELL(br + 3, bc + 3);


    // --- Pattern 3: Clock (4x4) ---
    // Placed in the top-right corner.
    int clr = 10, clc = 106; // Clock start row and column
    SET_CELL(clr, clc + 1);
    SET_CELL(clr + 1, clc);     SET_CELL(clr + 1, clc + 2);
    SET_CELL(clr + 2, clc + 1); SET_CELL(clr + 2, clc + 3);
    SET_CELL(clr + 3, clc + 2);


    // --- Pattern 4: Toad (2x4) ---
    // Placed in the bottom-left corner.
    int tr = 58, tc = 10; // Toad start row and column
    SET_CELL(tr, tc + 1); SET_CELL(tr, tc + 2); SET_CELL(tr, tc + 3);
    SET_CELL(tr + 1, tc); SET_CELL(tr + 1, tc + 1); SET_CELL(tr + 1, tc + 2);


    // --- Pattern 5: Blinker (1x3) ---
    // Placed in the bottom-right corner.
    int blr = 59, blc = 107; // Blinker start row and column
    SET_CELL(blr, blc);
    SET_CELL(blr, blc + 1);
    SET_CELL(blr, blc + 2);


    // Undefine the macro to prevent it from leaking outside this function.
    #undef SET_CELL
}



//GLIDER GUN:
//
//
void populate_with_glider_gun(int *array, int rows, int columns) {
    // 1. First, clear the entire board by setting all cells to 0 (dead).
    memset(array, 0, rows * columns * sizeof(int));

    // Define the dimensions of the Glider Gun pattern.
    const int gun_height = 9;
    const int gun_width = 36;

    // 2. Calculate the starting position to center the gun.
    // Integer division will handle centering automatically.
    int start_row = (rows - gun_height) / 2.9;
    int start_col = (columns - gun_width) / 2;

    // 3. Check if the gun can fit on the board.
    if (start_row < 0 || start_col < 0 || start_row + gun_height >= rows || start_col + gun_width >= columns) {
        printf("Warning: Board is too small to fit the Glider Gun. Board is empty.\n");
        return;
    }

    // 4. Define the 36 live cells of the Glider Gun pattern.
    // The coordinates are relative to the top-left of the pattern's bounding box.
    // We'll set the corresponding cells in the main array to 1 (alive).

    // Left Square (2x2 block)
    array[(start_row + 4) * columns + (start_col + 0)] = 1;
    array[(start_row + 5) * columns + (start_col + 0)] = 1;
    array[(start_row + 4) * columns + (start_col + 1)] = 1;
    array[(start_row + 5) * columns + (start_col + 1)] = 1;

    // Left "eater" part of the gun
    array[(start_row + 4) * columns + (start_col + 10)] = 1;
    array[(start_row + 5) * columns + (start_col + 10)] = 1;
    array[(start_row + 6) * columns + (start_col + 10)] = 1;
    array[(start_row + 3) * columns + (start_col + 11)] = 1;
    array[(start_row + 7) * columns + (start_col + 11)] = 1;
    array[(start_row + 2) * columns + (start_col + 12)] = 1;
    array[(start_row + 8) * columns + (start_col + 12)] = 1;
    array[(start_row + 2) * columns + (start_col + 13)] = 1;
    array[(start_row + 8) * columns + (start_col + 13)] = 1;
    array[(start_row + 5) * columns + (start_col + 14)] = 1;
    array[(start_row + 3) * columns + (start_col + 15)] = 1;
    array[(start_row + 7) * columns + (start_col + 15)] = 1;
    array[(start_row + 4) * columns + (start_col + 16)] = 1;
    array[(start_row + 5) * columns + (start_col + 16)] = 1;
    array[(start_row + 6) * columns + (start_col + 16)] = 1;
    array[(start_row + 5) * columns + (start_col + 17)] = 1;

    // Right "eater" part of the gun
    array[(start_row + 2) * columns + (start_col + 20)] = 1;
    array[(start_row + 3) * columns + (start_col + 20)] = 1;
    array[(start_row + 4) * columns + (start_col + 20)] = 1;
    array[(start_row + 2) * columns + (start_col + 21)] = 1;
    array[(start_row + 3) * columns + (start_col + 21)] = 1;
    array[(start_row + 4) * columns + (start_col + 21)] = 1;
    array[(start_row + 1) * columns + (start_col + 22)] = 1;
    array[(start_row + 5) * columns + (start_col + 22)] = 1;
    array[(start_row + 0) * columns + (start_col + 24)] = 1;
    array[(start_row + 1) * columns + (start_col + 24)] = 1;
    array[(start_row + 5) * columns + (start_col + 24)] = 1;
    array[(start_row + 6) * columns + (start_col + 24)] = 1;

    // Right Square (2x2 block)
    array[(start_row + 2) * columns + (start_col + 34)] = 1;
    array[(start_row + 3) * columns + (start_col + 34)] = 1;
    array[(start_row + 2) * columns + (start_col + 35)] = 1;
    array[(start_row + 3) * columns + (start_col + 35)] = 1;
}
