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

volatile map *currentMap;

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
  gDebug = false;
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
      currentMap = new map((char*)"/home/nova/2dgame/media/testMap", (char*)"/home/nova/2dgame/media/testMap", 128, 128, 3, 1);
      bool quit = false;
      character *playerCharacter = createPlayer();

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
        playerCharacter->rect->x = playerCharacter->locationX;
        playerCharacter->rect->y = playerCharacter->locationY;

        int distanceFromLeftEdge = playerCharacter->centerPos().x;
        int distanceFromRightEdge = gScreenWidth - playerCharacter->centerPos().x;
        int distanceFromTopEdge = playerCharacter->centerPos().y;
        int distanceFromBottomEdge = gScreenHeight - playerCharacter->centerPos().y;

        SDL_Point *cameraCenterPos = new SDL_Point();

        int cameraStopMarginX;
        int cameraStopMarginY;

        if (gScreenWidth < gScreenHeight)
        {
          cameraStopMarginX = gScreenWidth / 4;
          cameraStopMarginY = gScreenWidth / 4;
        }
        else
        {
          cameraStopMarginX = gScreenHeight / 4;
          cameraStopMarginY = gScreenHeight / 4;
        }

        if (distanceFromLeftEdge < cameraStopMarginX)
        {
          cameraCenterPos->x = cameraStopMarginX;
        } else if (distanceFromRightEdge < cameraStopMarginX)
        {
          cameraCenterPos->x = gScreenWidth - cameraStopMarginX;
        } else {
          cameraCenterPos->x = playerCharacter->centerPos().x;
        }
        if (distanceFromTopEdge < cameraStopMarginY)
        {
          cameraCenterPos->y = cameraStopMarginY;
        } else if (distanceFromBottomEdge < cameraStopMarginY)
        {
          cameraCenterPos->y = gScreenHeight - cameraStopMarginY;
        } else {
          cameraCenterPos->y = playerCharacter->centerPos().y;
        }

        // Calculate render port
        SDL_Rect *tileRenderBoundary = new SDL_Rect();
        vector tempViewportVector = playerCharacter->centerPos();
        tileRenderBoundary->x = tempViewportVector.x - gScreenWidth - 0.5*playerCharacter->width;
        tileRenderBoundary->y = tempViewportVector.y - gScreenHeight - 0.5*playerCharacter->height;
        tileRenderBoundary->w = gScreenWidth + gScreenWidth + playerCharacter->width;
        tileRenderBoundary->h = gScreenHeight + gScreenHeight + playerCharacter->height;
        int countX = 0;
        int countY = 0;
        for (int tileIndex = 0; tileIndex < currentMap->tileCountTotal; tileIndex++)
        {
          if (countX == currentMap->tileCountX)
          {
            countX = 0;
            countY ++;
          }
          SDL_Point *tilePos = new SDL_Point();
          tilePos->x = currentMap->tileWidth * countX - 1;
          tilePos->y = currentMap->tileHeight * countY;
          if (SDL_PointInRect(tilePos, tileRenderBoundary))
          {
            SDL_Rect *temp = new SDL_Rect();
            temp->x = tilePos->x;
            temp->y = tilePos->y;
            temp->w = currentMap->tileWidth;
            temp->h = currentMap->tileHeight;
            SDL_RenderCopy(gRenderer, currentMap->tiles[tileIndex], NULL, temp);
          }
          countX++;
        }
        SDL_RenderCopy(gRenderer, playerCharacter->texture, NULL, playerCharacter->rect);
        SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(gRenderer, tileRenderBoundary);
        SDL_Rect *debugCameraPosIndicator = new SDL_Rect();
        debugCameraPosIndicator->x = cameraCenterPos->x - 5;
        debugCameraPosIndicator->y = cameraCenterPos->y - 5;
        debugCameraPosIndicator->w = 10;
        debugCameraPosIndicator->h = 10;
        SDL_RenderFillRect(gRenderer, debugCameraPosIndicator);
        SDL_RenderPresent(gRenderer);
        SDL_PumpEvents();
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);
      }
    }
  }
  close();

  return 0;
}

character *createPlayer() {
  character *playerCharacter;
  playerCharacter = new character(gCharacterImage, 0.0f, 0.0f, 128, 128, 0, 4);
  playerCharacter->currentMap = 0;
  playerCharacter->texture = gCharacterImage;
  int width, height;
  SDL_QueryTexture(playerCharacter->texture, NULL, NULL, &width, &height);
  playerCharacter->height = width;
  playerCharacter->width = height;
  playerCharacter->rect->w = width;
  playerCharacter->rect->h = height;
  return playerCharacter;
}
