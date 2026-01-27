/*
    Styled button
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
#include "../object.hpp"
#include <SDL3/SDL.h>

namespace Scenes::Objects {
using namespace Scenes;

class Button : public TouchableSceneObject {
  SDL_FRect destRect;
  int horizontalWidth{6};
  int topHeight{5};
  int bottomHeight{9};

protected:
  // need to assign buttonTexture and nineSlice in this function
  virtual SDL_Texture *getTexture(SDL_Renderer *renderer) = 0;
  // virtual SDL_Surface *getDepressedTexture() = 0;

public:
  Button(float x, float y, float w, float h)
      : destRect(SDL_FRect{x, y, w, h}) {}

  void render(SDL_Renderer *renderer) {
    static SDL_Texture *texture{getTexture(renderer)};
    SDL_RenderTexture9Grid(renderer, texture, NULL, horizontalWidth,
                           horizontalWidth, topHeight, bottomHeight, 0.0F,
                           &destRect);
  }

  bool hitTest(float x, float y) {
    return (destRect.x <= x) && (x < destRect.x + destRect.w) &&
           (destRect.y <= y) && (y < destRect.y + destRect.h);
  }
};
} // namespace Scenes::Objects
