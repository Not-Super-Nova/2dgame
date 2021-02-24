//
// Created by nova on 20/02/2021.
//

#ifndef INC_2DGAME_MAP_HPP
#define INC_2DGAME_MAP_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <filesystem>
#include <exception>

class map {
public: bool valid();
public: map(char* tilePath, char*dataPath, int tileWidth, int tileHeight, int tileCountX, int tileCountY);
  int id;
  char* tilePath;
  char* collisionDataPath;
  int tileWidth;
  int tileHeight;
  int tileCountX;
  int tileCountY;
  int tileCountTotal;
  SDL_Texture *tiles[32];
  SDL_Rect* collisionBoxes[64];

public: SDL_Texture *render (SDL_Rect viewport);
  static int statFile(const char *tilePath);
};

struct mapLoadingException: public std::exception {
  const char * what () const throw() override
  {
    return "Error loading map"; //TODO: flesh out exception generation
  }
};

#endif//INC_2DGAME_MAP_HPP
