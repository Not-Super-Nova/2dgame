//
// Created by nova on 20/02/2021.
//

#include "map.hpp"
#include "loaders.hpp"
#include <sys/stat.h>

bool map::valid() {
  if (tileCountX * tileCountY > 32)
  {
    return false;
  }
  return true;
}
map::map(char *tilePath, char *dataPath, int tileWidth, int tileHeight, int tileCountX, int tileCountY) {
  bool error = false;
  this->tileCountX = tileCountX;
  this->tileCountY = tileCountY;
  if(!valid())
    throw mapLoadingException();
  int tilePathType = statFile(tilePath);
  int collisionDataPathType = statFile(dataPath);
  if (tilePathType == 1 && collisionDataPathType == 1)
  {
    tileCountTotal = 0;
    printf("Directories %s and %s are valid\n", tilePath, dataPath);
    char* texturePath = static_cast<char *>(malloc(4096));
    memset((void*)texturePath, '\0', 4096);
    snprintf(texturePath, 4096, "%s/%i.png", tilePath, 0);
    printf("%s\n", texturePath);
    tiles[0] = loadTexture(texturePath);
    SDL_QueryTexture(tiles[0], NULL, NULL, &this->tileWidth, &this->tileHeight);
    for (int i = 1; i < 32; i++)
    {
      snprintf(texturePath, 4096, "%s/%i.png", tilePath, i);
      printf("%s\n", texturePath);
      tiles[i] = loadTexture(texturePath);
      if (tiles[i] == NULL)
      {
        if (tileCountTotal == 0)
          tileCountTotal = i;
        else
          break;
      }
      int temph;
      int tempw;
      SDL_QueryTexture(tiles[i], NULL, NULL, &tempw, &temph);
      if (tempw != this->tileWidth || temph != this->tileHeight) {
        free(texturePath);
        throw mapLoadingException();
      }
      memset((void*)texturePath, '\0', 4096);
    }

    free(texturePath);
  }
  else
  {
    if (tilePathType != 1)
    {
      printf("Path %s is invalid\n", tilePath);
    }
    if (collisionDataPathType != 1)
    {
      printf("Path %s is invalid\n", dataPath);
    }
    throw mapLoadingException();
  }
}
int map::statFile(const char *path) {
  struct stat info{};
  printf("Current path: %s\n", path);
  if (stat(path, &info) != 0)
  {
    return 0;
  }
  else if (info.st_mode & S_IFDIR)
  {
    printf("%s is directory\n", path);
    return 1;
  }
  else
  {
    printf("%s is file\n", path);
    return 2;
  }
}
SDL_Texture *map::render(SDL_Rect viewport) {
  return tiles[1];
}
