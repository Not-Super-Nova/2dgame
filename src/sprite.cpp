//
// Created by nova on 19/02/2021.
//

#include "sprite.hpp"
Sprite::Sprite(SDL_Texture *texture, int locationX, int locationY, int width, int height, int currentMap) {
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
