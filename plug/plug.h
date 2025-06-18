#ifndef PLUG_H_
#define PLUG_H_
#include <SDL2/SDL.h>
typedef struct {
  SDL_Window *global_window;
  SDL_Surface *global_surface;   //can be obtained from the global window itself
  float dt;
} Plug;


#endif // PLUG_H_
