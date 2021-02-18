#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <string.h>

#include "constants.h"

SDL_Surface *loadSurface(char *path) {
  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(path);
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
  }

  return loadedSurface;
}

bool init() {

  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
    gWindow =
        SDL_CreateWindow(gcWindowTitle, SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, gcScreenWidth, gcScreenHeight,
                         SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {

      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }
  return success;
}

bool loadMedia() {
  // Loading success flag
  bool success = true;

  gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] =
      loadSurface((char *)"media/Default.png");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    printf("Failed to load %s", "Default.png");
    success = false;
  }

  gKeyPressSurfaces[KEY_PRESS_SURFACE_W] = loadSurface((char *)"media/W.png");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_W] == NULL) {
    printf("Failed to load %s", "W.png");
    success = false;
  }
  gKeyPressSurfaces[KEY_PRESS_SURFACE_S] = loadSurface((char *)"media/S.png");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_S] == NULL) {
    printf("Failed to load %s", "S.png");
    success = false;
  }
  gKeyPressSurfaces[KEY_PRESS_SURFACE_A] = loadSurface((char *)"media/A.png");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_A] == NULL) {
    printf("Failed to load %s", "A.png");
    success = false;
  }
  gKeyPressSurfaces[KEY_PRESS_SURFACE_D] = loadSurface((char *)"media/D.png");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_D] == NULL) {
    printf("Failed to load %s", "D.png");
    success = false;
  }

  return success;
}

void close() {

  SDL_FreeSurface(gTestImage);
  gTestImage = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  SDL_Quit();
}

int main(int argc, char *args[]) {
  if (!init()) {
    printf("Failed to initialize!\n");
  } else {
    if (!loadMedia()) {
      printf("Failed to load media!\n");
    } else {
      SDL_BlitSurface(gTestImage, NULL, gScreenSurface, NULL);
      SDL_UpdateWindowSurface(gWindow);

      bool quit = false;
      SDL_Event e;
      gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          switch (e.type) {
          case SDL_QUIT:
            printf("Quit requested, shutting down");
            quit = true;
            break;
          case SDL_KEYDOWN:
            switch (e.key.keysym.sym) {
            case SDLK_w:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_W];
              break;
            case SDLK_s:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_S];
              break;
            case SDLK_a:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_A];
              break;
            case SDLK_d:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_D];
              break;
            default:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
              break;
            }
            break;

          case SDL_KEYUP:
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
            break;
          }
        }
        SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

        SDL_UpdateWindowSurface(gWindow);
      }
    }
  }
  close();

  return 0;
}
