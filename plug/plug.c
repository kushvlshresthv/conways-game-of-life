#include "plug.h"


//forward declarations:
void draw_cell(SDL_Surface* surface, int cell_x, int cell_y);

void update(Plug *plug) {
    //render horizontal lines
    for(int i = 0; i*CELL_WIDTH < WINDOW_HEIGHT; i++) {
        SDL_FillRect(plug->global_surface, &(SDL_Rect){0,i*CELL_WIDTH,  WINDOW_WIDTH, GRID_THICKNESS}, COLOR_GREY);
    }

    //render te vertical lines
    for(int i = 0; i*CELL_WIDTH < WINDOW_WIDTH; i++) {
        SDL_FillRect(plug->global_surface, &(SDL_Rect){i*CELL_WIDTH,0,  GRID_THICKNESS,WINDOW_HEIGHT}, COLOR_GREY);
    }

    draw_cell(plug->global_surface, 20, 20);
    draw_cell(plug->global_surface, 22, 24);
    draw_cell(plug->global_surface, 25, 21);
}



void draw_cell(SDL_Surface* surface, int cell_x, int cell_y) {
    float pixel_x = cell_x * CELL_WIDTH;
    float pixel_y = cell_y * CELL_WIDTH;

    SDL_Rect cell =(SDL_Rect){ pixel_x, pixel_y, CELL_WIDTH, CELL_WIDTH };
    SDL_FillRect(surface, &cell ,COLOR_WHITE);
}
