//
// Created by nova on 20/02/2021.
//

#ifndef INC_2DGAME_GAMEMANAGER_HPP
#define INC_2DGAME_GAMEMANAGER_HPP

#include "../entities/character.hpp"
#include "../render/sprite.hpp"
#include "map.hpp"
#include <ctime>

class gameManager {
  tm *gameTime;
  map *currentMap;
  //playerCharacter *players[];
  character *characters[];
};

#endif//INC_2DGAME_GAMEMANAGER_HPP
