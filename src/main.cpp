#include <simple2d.h>
#include <string.h>

S2D_Image *testTile;
S2D_Window *window;
int moveSpeedMultiplier = 2;

void render() {
  // S2D_DrawCircle(320, 240, 64, 64, 1, 1, 1, 1);
  S2D_DrawImage(testTile);
}

void on_key(S2D_Event e) {
  switch (e.type) {
  case S2D_KEY_DOWN:
    if (strcmp(e.key, "Escape") == 0) {
      S2D_Close(window);
    } else if (strncmp(e.key, "W", 1) == 0) {
      testTile->y = (testTile->y - moveSpeedMultiplier);
    } else if (strncmp(e.key, "S", 1) == 0) {
      testTile->y = (testTile->y + moveSpeedMultiplier);
    } else if (strncmp(e.key, "A", 1) == 0) {
      testTile->x = (testTile->x - moveSpeedMultiplier);
    } else if (strncmp(e.key, "D", 1) == 0) {
      testTile->x = (testTile->x + moveSpeedMultiplier);
    }
    break;

  case S2D_KEY_HELD:
    if (strncmp(e.key, "W", 1) == 0) {
      testTile->y = (testTile->y - moveSpeedMultiplier);
    } else if (strncmp(e.key, "S", 1) == 0) {
      testTile->y = (testTile->y + moveSpeedMultiplier);
    } else if (strncmp(e.key, "A", 1) == 0) {
      testTile->x = (testTile->x - moveSpeedMultiplier);
    } else if (strncmp(e.key, "D", 1) == 0) {
      testTile->x = (testTile->x + moveSpeedMultiplier);
    }
    break;

  case S2D_KEY_UP:
    break;
  }
}

int main() {
  window = S2D_CreateWindow("Hello Triangle", 640, 480, NULL, render, 0);
  testTile = S2D_CreateImage("media/testTile.png");
  testTile->x = 0;
  testTile->y = 0;
  testTile->width = 128;
  testTile->height = 128;
  window->on_key = on_key;
  window->background.r = 1.0;
  window->background.g = 1.0;
  window->background.b = 1.0;
  window->background.a = 1.0;
  S2D_Show(window);
  return 0;
}
