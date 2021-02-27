//
// Created by nova on 26/02/2021.
//

#ifndef INC_2DGAME_UI_HPP
#define INC_2DGAME_UI_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <simple2d.h>

enum TextAlignment {
  TEXT_ALIGNMENT_LEFT,
  TEXT_ALIGNMENT_LEFT_UP,
  TEXT_ALIGNMENT_UP,
  TEXT_ALIGNMENT_RIGHT_UP,
  TEXT_ALIGNMENT_RIGHT,
  TEXT_ALIGNEMENT_DOWN_RIGHT,
  TEXT_ALIGNMENT_DOWN,
  TEXT_ALIGNMENT_DOWN_LEFT,
  TEXT_ALIGNMENT_CENTER
};

class UI {
  class RenderedItem {
  public:
    RenderedItem(SDL_Point *origin, int width, int height, SDL_Color *backgroundColor, SDL_Color *foregroundColor, SDL_Color *borderColor, int borderWidth, float *opacity);
    SDL_Point *origin;
    int width;
    int height;
    SDL_Color *backgroundColor{};
    SDL_Color *foregroundColor{};
    SDL_Color *borderColor{};
    int borderWidth;
    float *opacity;
    SDL_Rect *renderRect() {
      SDL_Rect *temp = new SDL_Rect();
      temp->x = origin->x;
      temp->y = origin->y;
      temp->w = width;
      temp->h = height;
      return temp;
    }
    SDL_Texture *texture;
    virtual void updateTexture() = 0;
  };

public:
  class TextBox : public RenderedItem {
  public:
    TextBox(SDL_Point *origin, int width, int height, SDL_Color *backgroundColor, SDL_Color *foregroundColor, SDL_Color *borderColor, int borderWidth, float *opacity, char *text, TTF_Font *font);
    char *text = (char *) "Sample Text";
    TTF_Font *font;
    void updateTexture() override;
  };

  class Image : public RenderedItem {
  };

  class BaseButton : public RenderedItem {};

  class TextButton : public BaseButton {};

  class ImageButton : public BaseButton {};

  class Slider : public RenderedItem {};

  class Bar : public RenderedItem {};
};

#endif//INC_2DGAME_UI_HPP
