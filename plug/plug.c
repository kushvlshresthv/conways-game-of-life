#include "plug.h"
#include <stdlib.h>
#include <stdio.h>
#include "patterns.h"
#include <stdbool.h>


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


Uint32 frame_start_time;
Uint32 FRAME_DELAY = 200;


void init(Plug *plug) {
    cells= malloc(rows * columns * sizeof(int));
    empty_cells= malloc(rows * columns * sizeof(int));
    if (cells == NULL || empty_cells == NULL) printf("Memory Allocation Failed, Handle It");

    populate_array_randomly(cells, rows, columns);
    /* populate_with_glider(cells, rows, columns, 20, 5); */
    /* populate_with_all_oscillators(cells, rows, columns); */
    /* populate_with_glider_gun(cells, rows, columns); */
}

void clear_grid() {
    memset(cells, 0, rows * columns * sizeof(int));
}


void populate_grid_with_oscillators() {
    populate_with_all_oscillators(cells, rows,columns);
}

void populate_grid_with_glider_gun() {
    populate_with_glider_gun(cells, rows, columns);
}

void populate_grid_with_random_cells() {
    populate_array_randomly(cells, rows, columns);
}




void draw_grid(Plug *plug) {
    //render horizontal lines
    for(int i = 0; i*CELL_WIDTH < WINDOW_HEIGHT; i++) {
        SDL_FillRect(plug->global_surface, &(SDL_Rect){0,i*CELL_WIDTH,  WINDOW_WIDTH, GRID_THICKNESS}, COLOR_GREY);
    }

    //render te vertical lines
    for(int i = 0; i*CELL_WIDTH < WINDOW_WIDTH; i++) {
        SDL_FillRect(plug->global_surface, &(SDL_Rect){i*CELL_WIDTH,0,  GRID_THICKNESS,WINDOW_HEIGHT}, COLOR_GREY);
    }
}




void update(Plug *plug) {

    frame_start_time = SDL_GetTicks();

    next_frame_cells();
    generate_pattern_from_matrix(plug->global_surface, rows, columns);
    draw_grid(plug);

    Uint32 frame_time = SDL_GetTicks() - frame_start_time;

    // 4. If frame time is less than the target delay, wait
    if (FRAME_DELAY > frame_time) {
        // 5. Delay for the remaining time to achieve the target FPS
        SDL_Delay(FRAME_DELAY - frame_time);
    }
}


Uint8 lerp(Uint8 a, Uint8 b, float t) {
    return a + (b - a) * t;
}

Uint32 color_lerp(float t, SDL_PixelFormat* format) {
    Uint8 r1 = (GRADIENT_TOP_COLOR >> 16) & 0xFF;
    Uint8 g1 = (GRADIENT_TOP_COLOR >> 8) & 0xFF;
    Uint8 b1 = GRADIENT_TOP_COLOR& 0xFF;

    Uint8 r2 = (GRADIENT_BOTTOM_COLOR >> 16) & 0xFF;
    Uint8 g2 = (GRADIENT_BOTTOM_COLOR >> 8) & 0xFF;
    Uint8 b2 = GRADIENT_BOTTOM_COLOR & 0xFF;

    Uint8 r = lerp(r1, r2, t);
    Uint8 g = lerp(g1, g2, t);
    Uint8 b = lerp(b1, b2, t);

    return SDL_MapRGB(format, r, g, b);
}

// Draw a rectangle with a vertical gradient based on its position in the window
void draw_rect_with_window_gradient(SDL_Surface* surface, SDL_Rect rect) {
    for (int y = 0; y < rect.h; y++) {
        int window_y = rect.y + y;
        float t = (float)window_y / surface->h;

        Uint32 pixel_color = color_lerp(t, surface->format);

        for (int x = 0; x < rect.w; x++) {
            SDL_Rect pixel_rect = { rect.x + x, rect.y + y, 1, 1 };
            SDL_FillRect(surface, &pixel_rect, pixel_color);
        }
    }
}




//takes the top corner of the cell and constructs
void draw_cell(SDL_Surface* surface, int cell_x, int cell_y, Uint32 color) {
    float pixel_x = cell_x * CELL_WIDTH;
    float pixel_y = cell_y * CELL_WIDTH;

    SDL_Rect cell =(SDL_Rect){ pixel_x, pixel_y, CELL_WIDTH, CELL_WIDTH };
    /* SDL_FillRect(surface, &cell ,color); */

    draw_rect_with_window_gradient(surface, cell);
}


void toggle_cell_state(Plug *plug, int cell_x, int cell_y) {
    float pixel_x = cell_x * CELL_WIDTH;
    float pixel_y = cell_y * CELL_WIDTH;

    SDL_Rect cell =(SDL_Rect){ pixel_x, pixel_y, CELL_WIDTH, CELL_WIDTH };
    if(cells[cell_y*columns + cell_x] == 1) {
        SDL_FillRect(plug->global_surface, &cell, COLOR_BLACK );
        cells[cell_x*columns + cell_y] = 0;
    }
    else {
        draw_rect_with_window_gradient(plug->global_surface, cell);
        cells[cell_y*columns + cell_x] = 1;
    }

    draw_grid(plug);
}




//colors the cells base on the its state
void generate_pattern_from_matrix(SDL_Surface* surface, int rows, int columns) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            if(cells[i*columns + j] == 1) {
                draw_cell(surface, j, i, COLOR_WHITE);
            } else {
                //The background is already black
                /* draw_cell(surface, j, i, COLOR_BLACK); */
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
