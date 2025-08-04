#include "plug.h"
#include <stdlib.h>
#include <stdio.h>


//forward declarations:
void draw_cell(SDL_Surface* surface, int cell_x, int cell_y, Uint32 color);
void populate_array_randomly(int* array, int rows, int columns);
void generate_pattern_from_matrix(SDL_Surface* surface, int rows, int columns);
void next_frame_cells();


//global variables:
int rows = WINDOW_HEIGHT / CELL_WIDTH;     //rows in the grid
int columns = WINDOW_WIDTH / CELL_WIDTH;   //columns in the grid
int *cells;
int *empty_cells;


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

void init(Plug *plug) {
    cells= malloc(rows * columns * sizeof(int));
    empty_cells= malloc(rows * columns * sizeof(int));
    if (cells == NULL || empty_cells == NULL) printf("Memory Allocation Failed, Handle It");

    /* populate_array_randomly(cells, rows, columns); */
    populate_with_glider(cells, rows, columns, 5, 5);
}


void update(Plug *plug) {
    SDL_Delay(500);
    next_frame_cells();
    generate_pattern_from_matrix(plug->global_surface, rows, columns);

    //render horizontal lines
    for(int i = 0; i*CELL_WIDTH < WINDOW_HEIGHT; i++) {
        SDL_FillRect(plug->global_surface, &(SDL_Rect){0,i*CELL_WIDTH,  WINDOW_WIDTH, GRID_THICKNESS}, COLOR_GREY);
    }

    //render te vertical lines
    for(int i = 0; i*CELL_WIDTH < WINDOW_WIDTH; i++) {
        SDL_FillRect(plug->global_surface, &(SDL_Rect){i*CELL_WIDTH,0,  GRID_THICKNESS,WINDOW_HEIGHT}, COLOR_GREY);
    }
}



//takes the top corner of the cell and constructs
void draw_cell(SDL_Surface* surface, int cell_x, int cell_y, Uint32 color) {
    float pixel_x = cell_x * CELL_WIDTH;
    float pixel_y = cell_y * CELL_WIDTH;

    SDL_Rect cell =(SDL_Rect){ pixel_x, pixel_y, CELL_WIDTH, CELL_WIDTH };
    SDL_FillRect(surface, &cell ,color);
}



//populates the cells with either 1 or 0 randomly
void populate_array_randomly(int *array, int rows, int columns) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j <columns; j++) {
            array[i*columns + j] = rand() % 2;
        }
    }
}


//colors the cells base on the its state
void generate_pattern_from_matrix(SDL_Surface* surface, int rows, int columns) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            if(cells[i*columns + j] == 1) {
                draw_cell(surface, i, j, COLOR_WHITE);
            } else {
                draw_cell(surface, i, j, COLOR_BLACK);
            }
        }
    }
}




int count_neighbours(int i, int j) {
    //left hand neightbours
    int neighbour_count = 0;
    if(j>0) neighbour_count += cells[i*columns + j-1];

    //right hand neighbours
    if(j<columns-1) neighbour_count += cells[i*columns + j + 1];

    //top neighbours
    if(i > 0) neighbour_count += cells[(i-1)*columns + j];

    //bottom neighbours
    if(i<rows - 1) neighbour_count += cells[(i+1)*columns + j];

    //top left neighbours
    if(j>0 && i>0) neighbour_count += cells[(i-1)*columns + j - 1];

    //bottom left neighbour
    if(j > 0 && i<rows-1) neighbour_count += cells[(i+1)*columns + j - 1];

    //top right neighbour
    if(j<columns-1 && i>0) neighbour_count += cells[(i-1)*columns + j + 1];

    //top left neighbour
    if(j<columns-1 && i < rows-1) neighbour_count += cells[(i+1)*columns + j + 1];

    return neighbour_count;
}


//calculates the cell states for the next frame
void next_frame_cells() {
    for(int i = 0; i<rows; i++) {
        for(int j = 0; j< columns; j++) {
            int neighbour_count = count_neighbours(i, j);

            printf("neighbour_count = %d\n", neighbour_count);
            //rule 1: a live cell with fewer than 2 live neighbours dies
            if(neighbour_count < 2) {
                empty_cells[i*columns + j] = 0;
                continue;
            }

            //rule 2: a live cell with 2 or 3 live neighbours live one
            if(neighbour_count == 2 || neighbour_count ==3) {

                //rule 4: A dead cell with exactly 3 neighbours become alive
                if(neighbour_count == 3) {
                    empty_cells[i*columns + j] = 1;
                    continue;
                }

                empty_cells[i*columns + j] = cells[i*columns + j];
                continue;
            }

            //rule 3: A live cell with more than 3 neighbours dies
            if(neighbour_count > 3) {
                empty_cells[i*columns + j] = 0;
                continue;
            }


        }
    }
    int *temp = cells;
    cells = empty_cells;
    empty_cells = temp;
}
