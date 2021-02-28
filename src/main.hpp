#include "entities/character.hpp"
#include <SDL2/SDL.h>

enum NextScene {
  SCENE_MAIN_MENU,
  SCENE_IN_GAME,
  SCENE_CUTSCENE,
  SCENE_SETTINGS,
  SCENE_ABOUT,
  SCENE_PAUSE_MENU
};

extern int gScreenWidth;
extern int gScreenHeight;
extern char *gcWindowTitle;
extern const char *gMediaPath;

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern Uint8 *gKeyboardState;
extern int gMovementSpeed;
extern SDL_Texture *gCharacterImage;
extern bool gDebug;
extern NextScene gNextScene;
extern bool gQuit;
const int gcTileCount = 32;

extern map *currentMap;
void windowUpdate(SDL_Event event);
bool inGameKeyboardHandler(character *player);
void runSceneInGame();

struct initException : public std::exception {
  [[nodiscard]] const char *what() const noexcept override {
    return "Failed to initialise game engine, quitting.";//TODO: flesh out exception generation
  }
};

struct mediaException : public std::exception {
  [[nodiscard]] const char *what() const noexcept override {
    return "Failed to load required game media, quitting.";//TODO: flesh out exception generation
  }
};