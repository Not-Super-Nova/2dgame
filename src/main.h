#include <SDL2/SDL.h>
enum LocationIDs { MAP_NONE };
typedef struct {
  SDL_Surface *surface;
  bool walkable;
  int locationX;
  int locationY;
} Tile;