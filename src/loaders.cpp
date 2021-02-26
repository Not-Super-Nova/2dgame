//
// Created by nova on 19/02/2021.
//
#include "loaders.hpp"
#include "main.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keyboard.h>

bool init() {

  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
    if (gDebug) {
      gScreenWidth = 1280;
      gScreenHeight = 720;
      gWindow = SDL_CreateWindow(gcWindowTitle, SDL_WINDOWPOS_UNDEFINED,
                           SDL_WINDOWPOS_UNDEFINED, gScreenWidth, gScreenHeight,
                           SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE /*| SDL_WINDOW_FULLSCREEN*/);
    }
    else {
      gWindow = SDL_CreateWindow(gcWindowTitle, SDL_WINDOWPOS_UNDEFINED,
                           SDL_WINDOWPOS_UNDEFINED, gScreenWidth, gScreenHeight,
                           SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    }
    if (gWindow == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      gRenderer = SDL_CreateRenderer(
          gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      SDL_GetWindowSurface(gWindow);
    }
  }

  gKeyboardState = (Uint8 *) SDL_GetKeyboardState(NULL);

  return success;
}

SDL_Surface *loadSurface(char *path) {
  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(path);
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
    return NULL;
  } else {
    return loadedSurface;
  }
}

SDL_Texture *loadTexture(char *path) {
  SDL_Texture *loadedTexture = IMG_LoadTexture(gRenderer, path);
  if (loadedTexture == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
    return NULL;
  } else {
    return loadedTexture;
  }
}

bool loadMedia() {
  bool success = true;

  gCharacterImage = loadTexture((char *) "media/character.png");

  return success;
}

// Destroy objects ready for closing
// TODO: map textures
void unload() {
  SDL_DestroyTexture(gCharacterImage);
  gCharacterImage = NULL;

  SDL_DestroyRenderer(gRenderer);
  gRenderer = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  SDL_Quit();
}