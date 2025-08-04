#include <math.h>
#include <windows.h>
#include "SDL_keycode.h"
#include "SDL_surface.h"
#include "SDL_video.h"
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <../plug/plug.h>


void next_frame();



Plug plug = {0};

bool init_sdl() {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not be initialized: %s", SDL_GetError());
    return false;
  }

  plug.global_window = SDL_CreateWindow("Bouncing Ball", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);

  if(plug.global_window==NULL) {
    printf("SDL Window could not be created: %s", SDL_GetError());
    return false;
  }
  plug.global_surface = SDL_GetWindowSurface(plug.global_window);

  return true;
}



void close() {
  SDL_DestroyWindow(plug.global_window);
  plug.global_window = NULL;
  plug.global_surface = NULL;
  SDL_Quit();
}




/* //global variables */
void (*init_ptr)(Plug *);
void (*update_ptr)(Plug *);
void (*clear_grid_ptr)();
void (*toggle_cell_state_ptr)(Plug *, int, int);
HMODULE plug_dll;





bool hot_reload() {

    if(plug_dll) {
      FreeLibrary(plug_dll);
    }

   int result = system(
      "gcc -shared -o ../build/plug.dll ../plug/plug.c ../plug/patterns.c "
      "-I../dependencies/SDL2-2.32.6/x86_64-w64-mingw32/include "
      "../dependencies/SDL2-2.32.6/x86_64-w64-mingw32/lib/libSDL2main.a "
      "../dependencies/SDL2-2.32.6/x86_64-w64-mingw32/lib/libSDL2.a "
      "-lmingw32 "
      "-lsetupapi -limm32 -lversion -lwinmm -lkernel32 -luser32 -lgdi32 -lwinspool "
      "-lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32 "
      "-Wl,--out-implib,../build/libplug.dll.a"
  );

    if(result !=0) {
      printf("DLL recompilation failed.\n");
      return false;
    }


    //we need to copy the .dll as window locks the currently used file and prevents the recompilation
    CopyFile("../build/plug.dll", "../build/plug_temp.dll", FALSE);
    plug_dll = LoadLibrary("../build/plug_temp.dll");

    init_ptr = (void (*)(Plug *))GetProcAddress(plug_dll, "init");

    update_ptr = (void (*)(Plug *))GetProcAddress(plug_dll, "update");

    clear_grid_ptr = (void (*)(void))GetProcAddress(plug_dll, "clear_grid");


    toggle_cell_state_ptr = (void (*)(Plug *, int, int))GetProcAddress(plug_dll, "toggle_cell_state");

    return true;
}





int main(int argc, char* argv[]) {


  //load sdl
  if(!init_sdl()) {
    return 1;
  }


  //hot reload the functions
  if(!hot_reload()) {
    printf("Hot reloading failed");
    return 1;
  }



  //variables:
  bool quit  = false;
  bool pause = false;
  init_ptr(&plug);

  while(!quit) {

    //event handling:
    SDL_Event e;
    while(SDL_PollEvent(&e)) {

      if(e.type == SDL_QUIT) {
        quit = true;
      }


      if(e.type == SDL_KEYDOWN) {

        switch(e.key.keysym.sym) {
          case SDLK_ESCAPE:
            quit = true;
            break;

          case SDLK_r:
            hot_reload();
            init_ptr(&plug);
            break;

          case SDLK_SPACE:
            pause = !pause;
            break;

          case SDLK_n:
            if(pause) {
              next_frame();
            }
            break;

          case SDLK_c:
            pause = true;
            clear_grid_ptr();
            next_frame();
            break;
        }


       /*
       ** REQUIREMENTS:
       ** When i press space bar, the animation should pause
       ** when i press 'c', the grid should clear and then pause
       ** after pausing, when i press 'n', the next frame should be rendered
       ** when the screen in pause, the user should be able to draw on the screen
        */



      }

      if(e.type == SDL_MOUSEBUTTONDOWN) {
        if(pause) {
          float x_f = e.button.x;
          float y_f = e.button.y;

          int x = floorf(x_f/CELL_WIDTH);
          int y = floorf(y_f/CELL_WIDTH);


          toggle_cell_state_ptr(&plug, x, y);
          SDL_UpdateWindowSurface(plug.global_window);

          printf("%d %d\n", x, y);
        }
      }

    }

    if(!pause) {
      next_frame();
    }
  }



  close();
  return 0;
}

void next_frame() {

    //clear the screen int width, height;
    SDL_FillRect(plug.global_surface, &(SDL_Rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, COLOR_BLACK);

    update_ptr(&plug);
    SDL_UpdateWindowSurface(plug.global_window);
}
