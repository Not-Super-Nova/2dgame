//
// Created by nova on 26/02/2021.
//

#ifndef INC_2DGAME_UI_HPP
#define INC_2DGAME_UI_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class UI {
  class RenderedItem{
    SDL_Point *origin;
    int width;
    int height;
    SDL_Color *backgroundColor;
    SDL_Color *foregroundColor;
    float *opacity;
    SDL_Rect *renderRect()
    {
      SDL_Rect *temp = new SDL_Rect();
      temp->x = origin->x;
      temp->y = origin->y;
      temp->w = width;
      temp->h = height;
      return temp;
    }
  };
  class TextBox : public RenderedItem{};
  class Image : public RenderedItem{};
  class BaseButton : public RenderedItem{};
  class TextButton : public BaseButton{};
  class ImageButton : public BaseButton{};
  class Slider : public RenderedItem{};
  class Bar : public RenderedItem{};
};

#endif//INC_2DGAME_UI_HPP
