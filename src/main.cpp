#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstdio>
#include <cstring>

#include "loaders.h"
#include "sprite.h"

#include "main.h"

#include "constants.h"

#include "globals.h"

Sprite *createPlayer();

void close() {

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
      Sprite *playerCharacter = createPlayer();

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
      }
    }
  }
  close();

  return 0;
}

Sprite *createPlayer() {
  Sprite *playerCharacter;
  playerCharacter = new Sprite(gCharacterImage, 0.0f, 0.0f, 128, 128, 0);
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
  return playerCharacter;
}
