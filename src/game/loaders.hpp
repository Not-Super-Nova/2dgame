//
// Created by nova on 19/02/2021.
//

#ifndef INC_2DGAME_LOADERS_HPP
#define INC_2DGAME_LOADERS_HPP

#include <SDL2/SDL.h>

bool init();
bool loadMedia();
SDL_Texture *loadTexture(char *path);
SDL_Surface *loadSurface(char *path);
void unload();
#endif// INC_2DGAME_LOADERS_HPP
