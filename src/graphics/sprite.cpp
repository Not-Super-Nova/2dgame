#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include "sprite.hpp"

Sprite::Sprite(SDL_Texture *texture, SDL_Point *worldPos, map *currentMap) {
  this->texture = texture;
  int tempWidth = 0;
  int tempHeight = 0;
  SDL_QueryTexture(texture, NULL, NULL, &tempWidth, &tempHeight);
  this->width = tempWidth;
  this->height = tempHeight;
  this->worldPos = worldPos;
  this->currentMap = currentMap;
}
