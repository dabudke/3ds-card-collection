/*
    Scene object data and render functionality
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
#include <SDL3/SDL.h>
#include <vector>

namespace Scenes::Objects {
struct SceneObject {
protected:
  float x;
  float y;

public:
  virtual void draw(SDL_Renderer *renderer, const int parentWidth,
                    const int parentHeight);
};

class BranchSceneObject : public SceneObject {
  std::vector<SceneObject> children;
};
class TouchableSceneObject : public SceneObject {
public:
  virtual SDL_FRect getHitbox();
};
} // namespace Scenes::Objects
