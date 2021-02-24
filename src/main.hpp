#include <SDL2/SDL.h>
enum LocationIDs { MAP_NONE };
typedef struct {
  SDL_Surface *surface;
  bool walkable;
  int locationX;
  int locationY;
} Tile;

extern int gScreenWidth;
extern int gScreenHeight;
extern char *gcWindowTitle;

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern Uint8 *gKeyboardState;
extern int gMovementSpeed;
extern SDL_Texture *gCharacterImage;
const int gcTileCount = 32;