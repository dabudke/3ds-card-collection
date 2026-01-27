#include "sceneManager.hpp"
#include <memory>
#include <stdexcept>

namespace Scenes {
Scenes::SceneManager::SceneManager(Scene *initialScene) {
  currentScene = std::unique_ptr<Scene>(initialScene);
}

SceneManager::~SceneManager() {}

void SceneManager::render() {
  if (currentScene == nullptr) {
    throw std::runtime_error("SceneManager not initialized yet");
  }
  SceneContext context;

  currentScene->render(context);
}
} // namespace Scenes
