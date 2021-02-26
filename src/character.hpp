//
// Created by nova on 22/02/2021.
//

#ifndef INC_2DGAME_CHARACTER_HPP
#define INC_2DGAME_CHARACTER_HPP

#include "map.hpp"
#include "sprite.hpp"
#include "vector.hpp"

class character : public Sprite {
public:
  character(SDL_Texture *texture, SDL_Point *worldPos, map *currentMap, int movementSpeed);
  int _movementSpeed;
  int _slowMovementSpeed;

public:
  SDL_Point *screenPos(vector *offset);

public:
  void move(int deltaX, int deltaY);

public:
  void setLocation(map *Map, SDL_Point *worldspace);

public:
  void setCoords(SDL_Point *worldspace);
};

#endif//INC_2DGAME_CHARACTER_HPP
