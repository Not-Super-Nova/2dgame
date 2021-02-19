//
// Created by nova on 19/02/2021.
//

#ifndef INC_2DGAME_SPRITE_H
#define INC_2DGAME_SPRITE_H

#include <SDL2/SDL.h>

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

#endif// INC_2DGAME_SPRITE_H
