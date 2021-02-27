#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "entities/character.hpp"
#include "game/loaders.hpp"

#include "graphics/UI.hpp"

#include "main.hpp"

// TODO: make this set from actual screen. Not everyone has a FHD screen any more.
int gScreenWidth = 1920;
int gScreenHeight = 1080;
char *gcWindowTitle = (char *) "Simple 2D Game";

SDL_Window *gWindow;
SDL_Renderer *gRenderer;
Uint8 *gKeyboardState;
int gMovementSpeed = 5;
SDL_Texture *gCharacterImage;
bool gDebug = true;
bool gQuit = false;
NextScene gNextScene = SCENE_MAIN_MENU;

map *currentMap;

void runSceneMainMenu();
int main() {
  if (!init())
    throw initException();
  if (!loadMedia())
    throw mediaException();

  while (!gQuit) {
    switch (gNextScene) {
      case SCENE_MAIN_MENU:
        runSceneMainMenu();
        break;
      case SCENE_IN_GAME:
        runSceneInGame();
        break;
      case SCENE_ABOUT:
        // TODO: runSceneAbout();
        gQuit = true;
        break;
      case SCENE_SETTINGS:
        // TODO: runSceneSettings();
        gQuit = true;
        break;
      case SCENE_CUTSCENE:
        // TODO: runSceneCutscene();
        gQuit = true;
        break;
      case SCENE_PAUSE_MENU:
        // TODO: runScenePauseMenu();
        gQuit = true;
        break;
    }
  }
  unload();

  return 0;
}

void runSceneMainMenu() {
  TTF_Font *titleFont = TTF_OpenFont((char *) "/home/nova/2dgame/media/OpenSans-Light.ttf", 30);
  if (titleFont == NULL) {
    printf("%s\n", TTF_GetError());
    throw mediaException();
  }
  SDL_Point *menuTextBoxOrigin = new SDL_Point();
  menuTextBoxOrigin->x = 0;
  menuTextBoxOrigin->y = gScreenHeight / 4;
  SDL_Color *backgroundColor = new SDL_Color();
  backgroundColor->r = 0;
  backgroundColor->g = 0;
  backgroundColor->b = 0;
  backgroundColor->a = 255;
  SDL_Color *white = new SDL_Color();
  white->r = 255;
  white->g = 255;
  white->b = 255;
  white->a = 255;
  UI::TextBox *titleTextBox = new UI::TextBox(menuTextBoxOrigin, backgroundColor, white, NULL, NULL, NULL, gcWindowTitle, titleFont);
  titleTextBox->origin->x = (gScreenWidth / 2) - (titleTextBox->width / 2);
  titleTextBox->updateTexture();
  bool continueMenu = true;
  while (continueMenu) {
    // Create new SDL_Event object, named event
    SDL_Event event;
    // Loop through all events available from the SDL2 library
    // the "&event" section means that it sets the event variable to the next available event to process
    while (SDL_PollEvent(&event)) {
      // If the event is a window event,
      if (event.type == SDL_WINDOWEVENT)
        // Send to function specific to window events
        windowUpdate(event);
      if (event.type == SDL_MOUSEBUTTONDOWN) {
        SDL_Point *mousePosition = new SDL_Point();
        SDL_GetMouseState(&mousePosition->x, &mousePosition->y);
        if (SDL_PointInRect(mousePosition, titleTextBox->renderRect())) {
          gNextScene = SCENE_IN_GAME;
          continueMenu = false;
        }
      }
    }
    SDL_RenderCopy(gRenderer, titleTextBox->texture, NULL, titleTextBox->renderRect());
    SDL_RenderPresent(gRenderer);
    SDL_PumpEvents();
    SDL_RenderClear(gRenderer);
  }
}

void runSceneInGame() {
  // Load test map
  // TODO: remove this, and replace with loading maps from saves / source
  currentMap = new map((char *) "/home/nova/2dgame/media/testMap",
                       (char *) "/home/nova/2dgame/media/testMap",
                       4,
                       8);

  // TODO: Load world position from save file
  SDL_Point *worldPos = new SDL_Point();
  worldPos->x = 0;
  worldPos->y = 0;

  character *player = new character(gCharacterImage, worldPos, currentMap, gMovementSpeed);

  SDL_Point *cameraWorldPos = new SDL_Point();
  cameraWorldPos->x = 0;
  cameraWorldPos->y = 0;

  bool stop = false;
  while (!stop) {

    // This line looks a little funky due to code generation
    // The 'inGameKeyboardHandler' returns the stop value
    // It's ugly, but it works.
    stop = inGameKeyboardHandler(player);

    gNextScene = SCENE_PAUSE_MENU;

    // Create new SDL_Event object, named event
    SDL_Event event;
    // Loop through all events available from the SDL2 library
    // the "&event" section means that it sets the event variable to the next available event to process
    while (SDL_PollEvent(&event)) {
      // If the event is a window event,
      if (event.type == SDL_WINDOWEVENT)
        // Send to function specific to window events
        windowUpdate(event);
    }

    // Calculate camera position on the X axis, according to screen size and world size
    if (player->worldPos->x < (gScreenWidth * 0.5) - (player->width * 0.5))
      cameraWorldPos->x = 0;
    else if (player->worldPos->x > currentMap->pixelCountX() - (0.5 * gScreenWidth) - (0.5 * player->width))
      cameraWorldPos->x = currentMap->pixelCountX() - gScreenWidth;
    else
      cameraWorldPos->x = (int)(player->worldPos->x - (gScreenWidth * 0.5) + (player->width * 0.5));

    // Calculate camera position on the Y axis, according to screen size and world size
    if (player->worldPos->y < (gScreenHeight * 0.5) - (player->height * 0.5))
      cameraWorldPos->y = 0;
    else if (player->worldPos->y > currentMap->pixelCountY() - (0.5 * gScreenHeight) - (0.5 * player->height))
      cameraWorldPos->y = currentMap->pixelCountY() - gScreenHeight;
    else
      cameraWorldPos->y = player->worldPos->y - (gScreenHeight * 0.5) + (player->height * 0.5);

    // Calculate where tiles, NPCs, etc, *have* to be rendered
    SDL_Rect *renderBoundary = new SDL_Rect();
    renderBoundary->x = 0;
    renderBoundary->y = 0;
    renderBoundary->w = gScreenWidth;
    renderBoundary->h = gScreenHeight;

    int countX = 0;
    int countY = 0;
    for (int tileIndex = 0; tileIndex < currentMap->tileCountTotal; tileIndex++) {
      if (countX == currentMap->tileCountX) {
        countX = 0;
        countY++;
      }

      // Get current tile origin (top left point)
      SDL_Point *tileWorldPos = new SDL_Point();
      tileWorldPos->x = currentMap->tileWidth * countX - 1;
      tileWorldPos->y = currentMap->tileHeight * countY;

      // Calculate where that point is in screen space
      SDL_Point *tileScreenPos = new SDL_Point();
      tileScreenPos->x = tileWorldPos->x - cameraWorldPos->x;
      tileScreenPos->y = tileWorldPos->y - cameraWorldPos->y;

      // Calculate area the tile would cover
      SDL_Rect *renderRectangle = new SDL_Rect();
      renderRectangle->x = tileScreenPos->x;
      renderRectangle->y = tileScreenPos->y;
      renderRectangle->w = currentMap->tileWidth;
      renderRectangle->h = currentMap->tileHeight;

      if (SDL_HasIntersection(renderRectangle, renderBoundary)) {
        // Tile in range, render it
        SDL_RenderCopy(gRenderer, currentMap->tiles[tileIndex], NULL, renderRectangle);
      }
      countX++;
    }

    //Render main character
    SDL_Rect *characterRenderRect = new SDL_Rect();
    SDL_Point *characterScreenPos = player->screenPos(new vector(cameraWorldPos->x, cameraWorldPos->y));
    characterRenderRect->x = characterScreenPos->x;
    characterRenderRect->y = characterScreenPos->y;
    characterRenderRect->w = player->width;
    characterRenderRect->h = player->height;
    SDL_RenderCopy(gRenderer, player->texture, NULL, characterRenderRect);

    // General SDL Library stuff for finishing render, and updating events
    SDL_RenderPresent(gRenderer);
    SDL_PumpEvents();
    SDL_RenderClear(gRenderer);
  }
}

bool inGameKeyboardHandler(character *player) {
  bool quit;
  if (gKeyboardState[SDL_SCANCODE_ESCAPE]) {
    printf("Quit requested, shutting down");
    quit = true;
  }
  if (gKeyboardState[SDL_SCANCODE_W]) {
    player->Move(0, -gMovementSpeed);
  }
  if (gKeyboardState[SDL_SCANCODE_S]) {
    player->Move(0, gMovementSpeed);
  }
  if (gKeyboardState[SDL_SCANCODE_A]) {
    player->Move(-gMovementSpeed, 0);
  }
  if (gKeyboardState[SDL_SCANCODE_D]) {
    player->Move(gMovementSpeed, 0);
  }
  return quit;
}

// "void" denotes function that doesn't return a value
void windowUpdate(SDL_Event event) {
  switch (event.window.event) {
      // In the case that the window size has changed,
    case SDL_WINDOWEVENT_RESIZED:
    case SDL_WINDOWEVENT_SIZE_CHANGED:
      // Set screen width and height according to data
      gScreenWidth = event.window.data1;
      gScreenHeight = event.window.data2;
      // And break so that other cases don't run
      break;
    // In the case that the window lost focus, or was hidden
    case SDL_WINDOWEVENT_HIDDEN:
    case SDL_WINDOWEVENT_FOCUS_LOST:
      // Add function that will likely be made with the UI
      // TODO: pauseGame();
      break;
    case SDL_WINDOWEVENT_CLOSE:
      exit(0);
    default:
      break;
  }
}
