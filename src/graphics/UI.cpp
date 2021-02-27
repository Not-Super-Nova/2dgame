//
// Created by nova on 26/02/2021.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../main.hpp"
#include "UI.hpp"

UI::RenderedItem::RenderedItem(SDL_Point *origin,
                               int width,
                               int height,
                               SDL_Color *backgroundColor,
                               SDL_Color *foregroundColor,
                               SDL_Color *borderColor,
                               int borderWidth,
                               float *opacity) {
  this->origin = origin;
  this->width = width;
  this->height = height;
  this->backgroundColor = backgroundColor;
  this->foregroundColor = foregroundColor;
  this->borderColor = borderColor;
  this->borderWidth = borderWidth;
  this->opacity = opacity;
}

UI::TextBox::TextBox(SDL_Point *origin, SDL_Color *backgroundColor,
                     SDL_Color *foregroundColor, SDL_Color *borderColor, int borderWidth,
                     float *opacity, char *text, TTF_Font *font) : RenderedItem(origin, width, height, backgroundColor, foregroundColor, borderColor, borderWidth, opacity) {
  this->text = text;
  this->font = font;
  this->origin = origin;
  this->backgroundColor = backgroundColor;
  this->foregroundColor = foregroundColor;
  this->borderColor = borderColor;
  this->borderWidth = borderWidth;
  this->opacity = opacity;
  TTF_SizeText(font, text, &width, &height);
}

void UI::TextBox::updateTexture() {
  SDL_Surface *message = TTF_RenderText_Shaded(this->font, this->text, *this->foregroundColor, *this->backgroundColor);
  this->texture = SDL_CreateTextureFromSurface(gRenderer, message);
  SDL_FreeSurface(message);
  SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height);
}
