//
// Created by nova on 22/02/2021.
//

#include "character.hpp"

void character::move(int deltaX, int deltaY) {
  this->worldPos->x += deltaX;
  this->worldPos->y += deltaY;
}

character::character(SDL_Texture *texture, SDL_Point *worldPos, map *currentMap, int movementSpeed) : Sprite(texture, worldPos, currentMap) {
  this->texture = texture;
  int tempWidth;
  int tempHeight;
  SDL_QueryTexture(texture, NULL, NULL, &tempWidth, &tempHeight);
  this->width = tempWidth;
  this->height = tempHeight;
  this->worldPos = worldPos;
  this->currentMap = currentMap;
  _movementSpeed = movementSpeed;
  _slowMovementSpeed = movementSpeed / 2;
}

SDL_Point *character::screenPos(vector *offset) {
  SDL_Point *output = new SDL_Point();
  output->x = this->worldPos->x - offset->x;
  output->y = this->worldPos->y - offset->y;
  return output;
}

void character::setCoords(SDL_Point *worldspace) {
  this->worldPos = worldspace;
}

void character::setLocation(map *Map, SDL_Point *worldspace) {
  this->currentMap = Map;
  this->worldPos = worldspace;
}
