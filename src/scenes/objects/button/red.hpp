/*
    Copyright (C) 2026  Daniel Budke

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https: //www.gnu.org/licenses/>.
*/

#pragma once
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "button.hpp"

namespace Scenes::Objects {

class RedButton : public Button {
  static SDL_Texture *buttonTexture;
  SDL_Texture *getTexture(SDL_Renderer *renderer) {
    if (buttonTexture == nullptr) {
      SDL_Surface *buttonSurface =
          SDL_LoadPNG("romfs:/ui/button_red_released.png");
      buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);
      SDL_DestroySurface(buttonSurface);
    }
    return buttonTexture;
  }

public:
  RedButton(float x, float y, float w, float h) : Button(x, y, w, h) {}

  ~RedButton() {
    if (buttonTexture != nullptr) {
      SDL_DestroyTexture(buttonTexture);
    }
  }
};

} // namespace Scenes::Objects
