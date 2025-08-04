#ifndef PLUG_H_
#define PLUG_H_
#include <SDL2/SDL.h>


//game constants:
#define WINDOW_WIDTH (CELL_WIDTH*120 + 1)   //this means 50 columns
#define WINDOW_HEIGHT (CELL_WIDTH*70 + 1)  //this means 50 rows
#define CELL_WIDTH 10 //NOTE: the CELL_WIDTH should be chosen carefully
#define GRID_THICKNESS 1


//colors:
#define COLOR_GREY 0x4a4a50
#define COLOR_BLACK 0x000000
#define COLOR_WHITE  0xffffff
#define GRADIENT_TOP_COLOR 0x7b42f5
#define GRADIENT_BOTTOM_COLOR 0xfa70fa



typedef struct {
    SDL_Window *global_window;
    SDL_Surface *global_surface;   //can be obtained from the global window itself
  float dt;
} Plug;


#endif // PLUG_H_
