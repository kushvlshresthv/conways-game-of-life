#ifndef PLUG_H_
#define PLUG_H_
#include <SDL2/SDL.h>


//game constants:
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800
#define ROWS 50
#define COLUMNS 50
#define GRID_THICKNESS 2


//colors:
#define COLOR_GREY 0x808080
#define COLOR_BLACK 0x000000




typedef struct {
  SDL_Window *global_window;
  SDL_Surface *global_surface;   //can be obtained from the global window itself
  float dt;
} Plug;


#endif // PLUG_H_
