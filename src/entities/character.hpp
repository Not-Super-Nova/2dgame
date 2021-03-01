//
// Created by nova on 22/02/2021.
//

#ifndef INC_2DGAME_CHARACTER_HPP
#define INC_2DGAME_CHARACTER_HPP

#include "../game/map.hpp"
#include "../graphics/sprite.hpp"
#include "../graphics/vector.hpp"

class character : public Sprite {
public:
  character(SDL_Texture *texture, SDL_Point *worldPos, map *currentMap, int movementSpeed);
  int _movementSpeed;
  int _slowMovementSpeed;

public:
  SDL_Point *screenPos(vector *offset);

public:
  void Move(int deltaX, int deltaY) override;

public:
  void setLocation(map *Map, SDL_Point *worldSpace);

public:
  void setCoords(SDL_Point *worldSpace);
};

#endif//INC_2DGAME_CHARACTER_HPP
