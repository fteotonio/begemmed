#include "GameState.h"

void GameState::update(int delta_time) {
  for (const auto& game_object: _game_objects) {
    game_object->update(delta_time);
  }
}

void GameState::render() const {
  for (const auto& game_object: _game_objects) {
    game_object->render();
  }
}

void GameState::addObject(GameObject* obj) {
  _game_objects.push_back(std::unique_ptr<GameObject>(obj));
}
