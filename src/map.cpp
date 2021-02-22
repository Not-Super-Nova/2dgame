//
// Created by nova on 20/02/2021.
//

#include "map.hpp"
#include <cassert>
#include <sys/stat.h>

bool map::valid() {
  if (tileCountX * tileCountY > 32)
  {
    return false;
  }
  return true;
}
map::map(char *tilePath, char *collisionDataPath, int tileWidth, int tileHeight, int tileCountX, int tileCountY) {
  bool error = false;
  int tilePathType = statFile(tilePath);
  printf("%i\n", (int*)tilePathType);
  int collisionDataPathType = statFile(collisionDataPath);
  printf("%i\n", (int*)collisionDataPathType);
  if (tilePathType == 1 && collisionDataPathType == 1)
  {
    printf("Directories %s and %s are valid", tilePath, collisionDataPath);
  }
  else
    error = true;
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
