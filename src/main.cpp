#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cstdio>
#include <cstring>

#include "main.h"

const int gcScreenWidth = 640;
const int gcScreenHeight = 480;
const char *gcWindowTitle = "Simple 2D Game";
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
Uint8 *gKeyboardState;
int gMovementSpeed = 2;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface *gCurrentSurface = NULL;
SDL_Texture *gCharacterImage = NULL;

SDL_Surface *loadSurface(char *path) {
  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(path);
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
    return NULL;
  } else {
    // SDL_Surface *optimizedSurface =
    //    SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
    // if (optimizedSurface == NULL) {
    //  printf("Failed to optimise %s: %s", path, SDL_GetError());
    return loadedSurface;
    //} else {
    //  return optimizedSurface;
  }
}

// return loadedSurface;
//}

SDL_Texture *loadTexture(char *path) {
  SDL_Texture *loadedTexture = IMG_LoadTexture(gRenderer, path);
  if (loadedTexture == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
    return NULL;
  } else {
    return loadedTexture;
  }
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
                         SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN*/);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      gRenderer = SDL_CreateRenderer(
          gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  gKeyboardState = (Uint8 *)SDL_GetKeyboardState(NULL);

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

  gCharacterImage = loadTexture((char *)"media/character.png");

  return success;
}

void close() {

  for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
    SDL_FreeSurface(gKeyPressSurfaces[i]);
  }

  SDL_DestroyTexture(gCharacterImage);
  gCharacterImage = NULL;

  SDL_DestroyRenderer(gRenderer);
  gRenderer = NULL;

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
      bool quit = false;
      SDL_Event e;
      gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
      Sprite *playerCharacter =
          new Sprite(gCharacterImage, 0.0f, 0.0f, 128, 128, 0);
      playerCharacter->currentMap = 0;
      playerCharacter->texture = gCharacterImage;
      int width, height;
      SDL_QueryTexture(playerCharacter->texture, NULL, NULL, &width, &height);
      playerCharacter->height = width;
      playerCharacter->width = height;
      playerCharacter->rect->w = width;
      playerCharacter->rect->h = height;
      playerCharacter->locationX = 0.0f;
      playerCharacter->locationY = 0.0f;

      while (!quit) {
        if (gKeyboardState[SDL_SCANCODE_ESCAPE]) {
          printf("Quit requested, shutting down");
          quit = true;
        }
        if (gKeyboardState[SDL_SCANCODE_W]) {
          playerCharacter->locationY -= gMovementSpeed;
        }
        if (gKeyboardState[SDL_SCANCODE_S]) {
          playerCharacter->locationY += gMovementSpeed;
        }
        if (gKeyboardState[SDL_SCANCODE_A]) {
          playerCharacter->locationX -= gMovementSpeed;
        }
        if (gKeyboardState[SDL_SCANCODE_D]) {
          playerCharacter->locationX += gMovementSpeed;
        }
        SDL_RenderClear(gRenderer);
        playerCharacter->rect->x = playerCharacter->locationX;
        playerCharacter->rect->y = playerCharacter->locationY;
        SDL_RenderCopy(gRenderer, playerCharacter->texture, NULL,
                       playerCharacter->rect);
        SDL_RenderPresent(gRenderer);
        SDL_RenderFillRect(gRenderer, playerCharacter->rect);
        SDL_PumpEvents();
        // SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

        // SDL_UpdateWindowSurface(gWindow);
      }
    }
  }
  close();

  return 0;
}
