//
// Created by nova on 20/02/2021.
//

#ifndef INC_2DGAME_MAP_HPP
#define INC_2DGAME_MAP_HPP

#include <SDL2/SDL_rect.h>
#include <filesystem>

class map {
public: bool valid();
public: map(char* tilePath, char* collisionDataPath, int tileWidth, int tileHeight, int tileCountX, int tileCountY);
  char* tilePath;
  char* collisionDataPath;
  int tileWidth;
  int tileHeight;
  int tileCountX;
  int tileCountY;
  char* tiles[32];
  SDL_Rect* collisionBoxes[];

  static int statFile(const char *tilePath) ;
};

#endif//INC_2DGAME_MAP_HPP
