//
// Created by nova on 20/02/2021.
//

#include "map.hpp"
#include "loaders.hpp"
#include <sys/stat.h>

// Calculate if map dimensions make sense, given array sizes
bool map::valid() {
  if (tileCountX * tileCountY > 32) {
    return false;
  }
  return true;
}

map::map(char *tilePath, char *dataPath, int tileWidth, int tileHeight, int tileCountX, int tileCountY) {

  this->tileCountX = tileCountX;
  this->tileCountY = tileCountY;

  if (!valid())
    throw mapLoadingException();

  int tilePathType = statFile(tilePath);
  int collisionDataPathType = statFile(dataPath);

  if (tilePathType == 1 && collisionDataPathType == 1) {
    printf("Directories %s and %s are valid\n", tilePath, dataPath);

    tileCountTotal = 0;

    // Create reusable memory area with Linux EXT4 filesystem path length limit. Subject to change.
    char *texturePath = static_cast<char *>(malloc(4096));
    memset((void *) texturePath, '\0', 4096);

    // Fill texturePath with actual path to first texture
    snprintf(texturePath, 4096, "%s/%i.png", tilePath, 0);

    tiles[0] = loadTexture(texturePath);

    // Get texture dimensions
    SDL_QueryTexture(tiles[0], NULL, NULL, &this->tileWidth, &this->tileHeight);

    for (int i = 1; i < 32; i++) {
      // Load next texture
      snprintf(texturePath, 4096, "%s/%i.png", tilePath, i);
      tiles[i] = loadTexture(texturePath);

      if (tiles[i] == NULL) {
        // Handle having less than 32 tiles
        if (tileCountTotal == 0)
          tileCountTotal = i;
        else
          break;
      }

      // Check dimensions match other tiles
      int temph;
      int tempw;
      SDL_QueryTexture(tiles[i], NULL, NULL, &tempw, &temph);
      if (tempw != this->tileWidth || temph != this->tileHeight) {
        free(texturePath);
        throw mapLoadingException();
      }

      // Clear previous path to avoid errors
      memset((void *) texturePath, '\0', 4096);
    }

    // Quick fix for having exactly 32 tiles
    if (tileCountTotal == 0 && tiles[0] != NULL) {
      tileCountTotal = 32;
    }

    // Free memory to avoid a leak
    free(texturePath);
  } else {
    // Something doesn't add up. Work out what here, and complain about it.
    if (tilePathType != 1) {
      printf("Path %s is invalid\n", tilePath);
    }
    if (collisionDataPathType != 1) {
      printf("Path %s is invalid\n", dataPath);
    }
    throw mapLoadingException();
  }
}

// Work out filesystem node type
int map::statFile(const char *path) {
  struct stat info {};
  printf("Current path: %s\n", path);
  if (stat(path, &info) != 0) {
    return 0;
  } else if (info.st_mode & S_IFDIR) {
    return 1;
  } else {
    return 2;
  }
}
