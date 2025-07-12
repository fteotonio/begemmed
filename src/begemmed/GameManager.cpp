#include "GameManager.h"

#include "src/engine/sound/SoundManager.h"
#include "src/engine/util/Timer.h"

#include <cmath>
#include <memory>

GameManager* GameManager::_game_manager {nullptr};

const int GameManager::cStartLevel {1};
const int GameManager::cStartScore {0};

GameManager* GameManager::instance() {
  if (!_game_manager) {
    _game_manager = new GameManager();
  }
  return _game_manager;
}

int GameManager::getLevel() const {
  return _level;
}

int GameManager::getScore() const {
  return _score;
}

int GameManager::getScoreToNextLevel(int level) const {
  return level == 0 ? 0 : (1000 * level + 400 * level * (level - 1));
}

void GameManager::addScore(int score) {
  _score += score;
  while (_score >= getScoreToNextLevel(_level)) {
    ++_level;
  }
}

void GameManager::resetGame() {
  _level = cStartLevel;
  _score = cStartScore;
}
