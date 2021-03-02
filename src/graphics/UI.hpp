//
// Created by nova on 26/02/2021.
//

#ifndef INC_2DGAME_UI_HPP
#define INC_2DGAME_UI_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

enum TextAlignment {
  TEXT_ALIGNMENT_LEFT,
  TEXT_ALIGNMENT_LEFT_UP,
  TEXT_ALIGNMENT_UP,
  TEXT_ALIGNMENT_RIGHT_UP,
  TEXT_ALIGNMENT_RIGHT,
  TEXT_ALIGNMENT_DOWN_RIGHT,
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
    [[nodiscard]] SDL_Rect *renderRect() const {
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
    TextBox(SDL_Point *origin, SDL_Color *backgroundColor, SDL_Color *foregroundColor, SDL_Color *borderColor, int borderWidth, float *opacity, char *text, TTF_Font *font);
    char *text;
    TTF_Font *font;
    void updateTexture() override;
  };

  class Image : public RenderedItem {
  };

  class BaseButton : public RenderedItem {
  public:
    BaseButton(SDL_Point *origin, SDL_Color *backgroundColor, SDL_Color *foregroundColor, SDL_Color *borderColor, int borderWidth, float *opacity, int width, int height);
  public: bool CheckClick(SDL_Point *clickLocation);
    void updateTexture() override;
  };

  class TextButton : public BaseButton {
  public:
    TextButton(SDL_Point *origin, SDL_Color *backgroundColor, SDL_Color *foregroundColor, SDL_Color *borderColor, int borderWidth, float *opacity, int width, int height, char *text, TTF_Font *font);
    char *text;
    TTF_Font *font;
    void updateTexture() override;
  };

  class ImageButton : public BaseButton {
    ImageButton() : BaseButton(nullptr,nullptr,nullptr,nullptr,0,nullptr,100,100) {}
  };

  class Slider : public RenderedItem {};

  class Bar : public RenderedItem {};
};

#endif//INC_2DGAME_UI_HPP
