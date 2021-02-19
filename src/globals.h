//
// Created by nova on 19/02/2021.
//

#ifndef INC_2DGAME_GLOBALS_H
#define INC_2DGAME_GLOBALS_H

#include <SDL2/SDL.h>

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
Uint8 *gKeyboardState;
int gMovementSpeed = 2;
SDL_Texture *gCharacterImage = NULL;

#endif// INC_2DGAME_GLOBALS_H
