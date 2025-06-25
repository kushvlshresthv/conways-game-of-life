#include "plug.h"
#include <stdlib.h>


//forward declarations:
void draw_cell(SDL_Surface* surface, int cell_x, int cell_y, Uint32 color);
void populate_array_randomly(int* array, int row, int column);
void generate_pattern_from_matrix(SDL_Surface* surface, int * array, int row, int column);


int row = WINDOW_HEIGHT / CELL_WIDTH;
int column = WINDOW_WIDTH / CELL_WIDTH;
int cells[100][100];

void init(Plug *plug) {
    populate_array_randomly(&cells[0][0], row, column);
}


void update(Plug *plug) {
    generate_pattern_from_matrix(plug->global_surface, &cells[0][0], row, column);

    //render horizontal lines
    for(int i = 0; i*CELL_WIDTH < WINDOW_HEIGHT; i++) {
        SDL_FillRect(plug->global_surface, &(SDL_Rect){0,i*CELL_WIDTH,  WINDOW_WIDTH, GRID_THICKNESS}, COLOR_GREY);
    }

    //render te vertical lines
    for(int i = 0; i*CELL_WIDTH < WINDOW_WIDTH; i++) {
        SDL_FillRect(plug->global_surface, &(SDL_Rect){i*CELL_WIDTH,0,  GRID_THICKNESS,WINDOW_HEIGHT}, COLOR_GREY);
    }
}



void draw_cell(SDL_Surface* surface, int cell_x, int cell_y, Uint32 color) {
    float pixel_x = cell_x * CELL_WIDTH;
    float pixel_y = cell_y * CELL_WIDTH;

    SDL_Rect cell =(SDL_Rect){ pixel_x, pixel_y, CELL_WIDTH, CELL_WIDTH };
    SDL_FillRect(surface, &cell ,color);
}



void populate_array_randomly(int *array, int row, int column) {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j <column; j++) {
            array[i*row + j] = rand() % 2;
        }
    }
}


void generate_pattern_from_matrix(SDL_Surface* surface, int* array, int row, int column) {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < column; j++) {
            if(array[i*row + j] == 1) {
                draw_cell(surface, i, j, COLOR_WHITE);
            } else {
                draw_cell(surface, i, j, COLOR_BLACK);
            }
        }
    }
}
