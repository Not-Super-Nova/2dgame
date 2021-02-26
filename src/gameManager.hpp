//
// Created by nova on 20/02/2021.
//

#ifndef INC_2DGAME_GAMEMANAGER_HPP
#define INC_2DGAME_GAMEMANAGER_HPP

#include "character.hpp"
#include "map.hpp"
#include "sprite.hpp"
#include <ctime>

class gameManager {
  tm *gameTime;
  map *currentMap;
  //playerCharacter *players[];
  character *characters[];
};

#endif//INC_2DGAME_GAMEMANAGER_HPP
