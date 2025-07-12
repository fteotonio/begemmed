#pragma once

#include "src/engine/util/Timer.h"

#include <memory>

class GameManager {
  public:
    static GameManager* instance();

    int getLevel() const;
    int getScore() const;
    int getScoreToNextLevel(int level) const;

    void addScore(int score);
    void resetGame();

  private:
    static GameManager* _game_manager;

    static const int cStartLevel;
    static const int cStartScore;

    int _level;
    int _score;

    GameManager() : _level(cStartLevel), _score(cStartScore) {}
};
