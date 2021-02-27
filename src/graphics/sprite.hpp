#ifndef INC_2DGAME_SPRITE_HPP
#define INC_2DGAME_SPRITE_HPP

#include "../game/map.hpp"
#include <SDL2/SDL.h>

class Sprite {
public:
  Sprite(SDL_Texture *texture, SDL_Point *worldPos, map *currentMap);

public:
  SDL_Texture *texture;

public:
  SDL_Point *worldPos;

public:
  virtual void Move(int deltaX, int deltaY) = 0;

public:
  int width;

public:
  int height;

public:
  map *currentMap;
};

#endif// INC_2DGAME_SPRITE_HPP
