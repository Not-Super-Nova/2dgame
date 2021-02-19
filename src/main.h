#include <SDL2/SDL.h>
enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_W,
  KEY_PRESS_SURFACE_A,
  KEY_PRESS_SURFACE_S,
  KEY_PRESS_SURFACE_D,
  KEY_PRESS_SURFACE_TOTAL
};
enum LocationIDs { MAP_NONE };
typedef struct {
  SDL_Surface *surface;
  bool walkable;
  int locationX;
  int locationY;
} Tile;
class Sprite {
public:
  Sprite(SDL_Texture *texture, float locationX, float locationY, int width,
         int height, int currentMap) {
    this->texture = texture;
    this->locationX = locationX;
    this->locationY = locationY;
    this->width = width;
    this->height = height;
    this->currentMap = currentMap;
    SDL_Rect *temp = new SDL_Rect();
    temp->x = this->locationX;
    temp->y = this->locationY;
    temp->h = this->height;
    temp->w = this->width;
    this->rect = temp;
  }

public:
  SDL_Texture *texture;

public:
  float locationX;

public:
  float locationY;

public:
  int width;

public:
  int height;

public:
  int currentMap;

public:
  SDL_Rect *rect;
};