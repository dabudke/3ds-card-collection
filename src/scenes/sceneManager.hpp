/*
    Scene, render, and touch management engine
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
#include "scene.hpp"
#include <SDL3/SDL.h>
#include <memory>
#include <stdexcept>

extern SDL_Renderer *topRenderer;
extern SDL_Renderer *bottomRenderer;

namespace Scenes {
class Scene;
struct SceneContext {
  void changeScene(std::unique_ptr<Scene> newScene);
};

class SceneManager {
  std::unique_ptr<Scene> currentScene;
  bool shouldExitFlag{false};

  friend SceneContext;

  bool hasInit() { return currentScene != nullptr; }

public:
  SceneManager(Scene *initialScene);
  ~SceneManager();

  void render();
  virtual void handleButtonDown(SDL_GamepadButton button);
  virtual void handleButtonUp(SDL_GamepadButton button);
  void handleTouch(float tx, float ty);

  bool shouldExit() { return shouldExitFlag; }
};
} // namespace Scenes
