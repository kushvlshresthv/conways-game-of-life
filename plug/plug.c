#include "plug.h"
#include <stdio.h>


void update(Plug *plug) {

    float cell_length = (float) WINDOW_HEIGHT / ROWS;


    //render horizontal lines
    for(int i = 0; i<ROWS; i++) {
        SDL_FillRect(plug->global_surface, &(SDL_Rect){0,i*cell_length,  WINDOW_WIDTH, GRID_THICKNESS}, COLOR_GREY);
    }

    //render te vertical lines
    for(int i = 0; i*cell_length < WINDOW_WIDTH; i++) {
        printf("Trying to render columns\n");
        SDL_FillRect(plug->global_surface, &(SDL_Rect){i*cell_length,0,  GRID_THICKNESS,WINDOW_HEIGHT}, COLOR_GREY);
    }
}
