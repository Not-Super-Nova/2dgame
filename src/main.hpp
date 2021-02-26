#include <SDL2/SDL.h>

extern int gScreenWidth;
extern int gScreenHeight;
extern char *gcWindowTitle;

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern Uint8 *gKeyboardState;
extern int gMovementSpeed;
extern SDL_Texture *gCharacterImage;
extern bool gDebug;
const int gcTileCount = 32;