/*
    Render loop and touch hit testing
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
#include "SDL3/SDL_gamepad.h"
#include "SDL3/SDL_pixels.h"
#include "objects/object.hpp"
#include "sceneManager.hpp"
#include <3ds/types.h>
#include <vector>

extern const int ScreenHeight;
extern const int TopScreenWidth;
extern const int BottomScreenWidth;

namespace Scenes {
struct SceneContext;
using namespace Objects;

class Scene {
  static const SDL_PixelFormat pixelFormat{SDL_PIXELFORMAT_RGBA8888};

protected:
  std::vector<SceneObject> topTree;
  std::vector<SceneObject> bottomTree;
  struct {
    u8 red;
    u8 green;
    u8 blue;
  } backgroundColor;

public:
  void render(SceneContext &context);

  virtual void handleButtonDown(SceneContext &context,
                                SDL_GamepadButton button);
  virtual void handleButtonUp(SceneContext &context, SDL_GamepadButton button);
  void handleTouchBegin(SceneContext &context, float tx, float ty);
  void handleTouchMove(SceneContext &context, float tx, float ty);
  void handleTouchEnd(SceneContext &context, float tx, float ty);

  virtual void handleTap(SceneContext &context, float tx, float ty);
  virtual void handleDragBegin(SceneContext &context, float tx, float ty);
  virtual void handleDragMove(SceneContext &context, float dx, float dy);
  virtual void handleDragEnd(SceneContext &context, float dx, float dy);
};
} // namespace Scenes
