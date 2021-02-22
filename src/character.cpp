//
// Created by nova on 22/02/2021.
//

#include "character.hpp"
void character::setLocation(map Map, vector Location) {
  this->currentMap = Map.id;
  this->locationX = Location.x;
  this->locationY = Location.y;
}
moveDirection character::calculateMovement() { // NOLINT(readability-convert-member-functions-to-static)
  return MOVE_NONE;
}
void character::setCoords(vector Location) {
  this->locationX = Location.x;
  this->locationY = Location.y;
}
void character::move(int deltaX, int deltaY) {
  this->locationX += deltaX;
  this->locationY += deltaY;
}
character::character(SDL_Texture *texture, int locationX, int locationY, int width, int height, int currentMap, int movementSpeed) : Sprite(texture, locationX, locationY, width, height, currentMap) {
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
  this->_movementSpeed = movementSpeed;
  this->_slowMovementSpeed = movementSpeed/2;
}
