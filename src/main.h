#include <SDL2/SDL.h>
enum LocationIDs { MAP_NONE };
typedef struct {
  SDL_Surface *surface;
  bool walkable;
  int locationX;
  int locationY;
} Tile;

const int gcScreenWidth = 512;
const int gcScreenHeight = 512;
const char *gcWindowTitle = "Simple 2D Game";

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
Uint8 *gKeyboardState;
int gMovementSpeed = 2;
SDL_Texture *gCharacterImage = NULL;