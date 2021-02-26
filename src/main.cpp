#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstdio>
#include <cstring>

#include "character.hpp"
#include "loaders.hpp"
#include "sprite.hpp"
#include "map.hpp"

#include "main.hpp"

int gScreenWidth = 512;
int gScreenHeight = 512;
char *gcWindowTitle = (char*) "2D Game";

SDL_Window *gWindow;
SDL_Renderer *gRenderer;
Uint8 *gKeyboardState;
int gMovementSpeed;
SDL_Texture *gCharacterImage;
bool gDebug;

map *currentMap;

character *createPlayer();

void close() {

  SDL_DestroyTexture(gCharacterImage);
  gCharacterImage = NULL;

  SDL_DestroyRenderer(gRenderer);
  gRenderer = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  SDL_Quit();
}

int main(int argc, char *argv[]) {
  gScreenWidth = 1920;
  gScreenHeight = 1080;
  gcWindowTitle = (char*) "Simple 2D Game";
  gMovementSpeed = 5;
  gDebug = true;
  if (!init()) {
    printf("Failed to initialize!\n");
    return -1;
  } else {
    if (!loadMedia()) {
      printf("Failed to load media!\n");
      return -1;
    } else {
      // Load test map
      // TODO: remove this, and replace with loading maps from saves / source
      currentMap = new map((char*)"/home/nova/2dgame/media/testMap", (char*)"/home/nova/2dgame/media/testMap", 512, 512, 4, 8);
      bool quit = false;
      SDL_Point *worldPos = new SDL_Point();
      worldPos->x = 0;
      worldPos->y = 0;
      character *player = new character(gCharacterImage, worldPos, currentMap, gMovementSpeed);

      SDL_Point *cameraWorldPos = new SDL_Point();
      cameraWorldPos->x = 0;
      cameraWorldPos->y = 0;

      while (!quit) {
        if (gKeyboardState[SDL_SCANCODE_ESCAPE]) {
          printf("Quit requested, shutting down");
          quit = true;
        }
        if (gKeyboardState[SDL_SCANCODE_W]) {
          player->move(0, -gMovementSpeed);
        }
        if (gKeyboardState[SDL_SCANCODE_S]) {
          player->move(0, gMovementSpeed);
        }
        if (gKeyboardState[SDL_SCANCODE_A]) {
          player->move(-gMovementSpeed, 0);
        }
        if (gKeyboardState[SDL_SCANCODE_D]) {
          player->move(gMovementSpeed, 0);
        }

        if (player->worldPos->x < (gScreenWidth * 0.5) - (player->width * 0.5))
          cameraWorldPos->x = 0;
        else if (player->worldPos->x > currentMap->pixelCountX() - (0.5 * gScreenWidth) - (0.5 * player->width))
          cameraWorldPos->x = currentMap->pixelCountX() - gScreenWidth;
        else
          cameraWorldPos->x = player->worldPos->x - (gScreenWidth * 0.5) + (player->width * 0.5);

        if (player->worldPos->y < (gScreenHeight * 0.5) - (player->height * 0.5))
          cameraWorldPos->y = 0;
        else if (player->worldPos->y > currentMap->pixelCountY() - (0.5 * gScreenHeight) - (0.5 * player->height))
          cameraWorldPos->y = currentMap->pixelCountY() - gScreenHeight;
        else
          cameraWorldPos->y = player->worldPos->y - (gScreenHeight * 0.5) + (player->height * 0.5);

        SDL_Rect *renderBoundary = new SDL_Rect();
        renderBoundary->x = 0;
        renderBoundary->y = 0;
        renderBoundary->w = gScreenWidth;
        renderBoundary->h = gScreenHeight;

        int countX = 0;
        int countY = 0;
        for (int tileIndex = 0; tileIndex < currentMap->tileCountTotal; tileIndex++)
        {
          if (countX == currentMap->tileCountX)
          {
            countX = 0;
            countY ++;
          }
          SDL_Point *tileWorldPos = new SDL_Point();
          tileWorldPos->x = currentMap->tileWidth * countX - 1;
          tileWorldPos->y = currentMap->tileHeight * countY;

          SDL_Point *tileScreenPos = new SDL_Point();
          tileScreenPos->x = tileWorldPos->x - cameraWorldPos->x;
          tileScreenPos->y = tileWorldPos->y - cameraWorldPos->y;

          SDL_Rect *renderRectangle = new SDL_Rect();
          renderRectangle->x = tileScreenPos->x;
          renderRectangle->y = tileScreenPos->y;
          renderRectangle->w = currentMap->tileWidth;
          renderRectangle->h = currentMap->tileHeight;
          if (SDL_HasIntersection(renderRectangle, renderBoundary))
          {
            SDL_RenderCopy(gRenderer, currentMap->tiles[tileIndex], NULL, renderRectangle);
          }
          countX++;
        }
        SDL_Rect *characterRenderRect = new SDL_Rect();
        SDL_Point *characterScreenPos = player->screenPos(new vector(cameraWorldPos->x, cameraWorldPos->y));
        characterRenderRect->x = characterScreenPos->x;
        characterRenderRect->y = characterScreenPos->y;
        characterRenderRect->w = player->width;
        characterRenderRect->h = player->height;
        SDL_RenderCopy(gRenderer, player->texture, NULL, characterRenderRect);
        SDL_RenderPresent(gRenderer);
        SDL_PumpEvents();
        SDL_RenderClear(gRenderer);
      }
    }
  }
  close();

  return 0;
}
