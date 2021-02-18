#include <SDL2/SDL.h>
const int gcScreenWidth = 640;
const int gcScreenHeight = 480;
const char *gcWindowTitle = "Simple 2D Game";
enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_W,
  KEY_PRESS_SURFACE_A,
  KEY_PRESS_SURFACE_S,
  KEY_PRESS_SURFACE_D,
  KEY_PRESS_SURFACE_TOTAL
};
SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface *gCurrentSurface = NULL;
SDL_Surface *gTestImage = NULL;