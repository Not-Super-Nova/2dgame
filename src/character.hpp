//
// Created by nova on 22/02/2021.
//

#ifndef INC_2DGAME_CHARACTER_HPP
#define INC_2DGAME_CHARACTER_HPP

#include "map.hpp"
#include "vector.hpp"
#include "sprite.hpp"

enum moveDirection {
  MOVE_NORTH,
  MOVE_NORTH_EAST,
  MOVE_EAST,
  MOVE_SOUTH_EAST,
  MOVE_SOUTH,
  MOVE_SOUTH_WEST,
  MOVE_WEST,
  MOVE_NORTH_WEST,
  MOVE_NONE
};

class character : public Sprite{
public: character(SDL_Texture *texture, SDL_Point *worldPos, map *currentMap, int movementSpeed);
  int _movementSpeed;
  int _slowMovementSpeed;
public: SDL_Point *screenPos(vector *offset);
public: moveDirection calculateMovement();
public: void move(int deltaX, int deltaY);
public: void setLocation (map *Map, SDL_Point *worldspace);
public: void setCoords (SDL_Point *worldspace);
};

#endif//INC_2DGAME_CHARACTER_HPP
