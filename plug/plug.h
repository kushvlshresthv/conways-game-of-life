#ifndef PLUG_H_
#define PLUG_H_
#include <SDL2/SDL.h>


//game constants:
#define WINDOW_WIDTH 902
#define WINDOW_HEIGHT 902
#define CELL_WIDTH (30/1.5) //NOTE: the CELL_WIDTH should be chosen carefully
#define GRID_THICKNESS 1


//colors:
#define COLOR_GREY 0x808080
#define COLOR_BLACK 0x000000
#define COLOR_WHITE  0xffffff




typedef struct {
    SDL_Window *global_window;
    SDL_Surface *global_surface;   //can be obtained from the global window itself
  float dt;
} Plug;


#endif // PLUG_H_
