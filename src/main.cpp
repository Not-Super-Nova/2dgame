#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

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

    gWindow = SDL_CreateWindow(gcWindowTitle, SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, gcScreenWidth,
                               gcScreenHeight, SDL_WINDOW_SHOWN);
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
  bool success = true;
  gTestImage = loadSurface((char *)"media/testTile.png");
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

      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            printf("Quit requested, shutting down");
            quit = true;
          }
        }
      }
    }
  }
  close();

  return 0;
}
