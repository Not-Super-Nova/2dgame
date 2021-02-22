//
// Created by nova on 19/02/2021.
//

#ifndef INC_2DGAME_SPRITE_HPP
#define INC_2DGAME_SPRITE_HPP

#include <SDL2/SDL.h>

class Sprite {
public:
  Sprite(SDL_Texture *texture, int locationX, int locationY, int width,
         int height, int currentMap) ;

public:
  SDL_Texture *texture;

public:
  int locationX;

public:
  int locationY;

public:
  int width;

public:
  int height;

public:
  int currentMap;

public:
  SDL_Rect *rect;
};

#endif// INC_2DGAME_SPRITE_HPP
