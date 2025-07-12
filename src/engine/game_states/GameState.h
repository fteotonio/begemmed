#pragma once

#include "src/engine/game_objects/GameObject.h"

#include <string>
#include <vector>

class GameState {
  public:
    virtual void update(int delta_time);
    virtual void render() const;

    void addObject(GameObject* obj);

    virtual ~GameState() = default;

  protected:
    std::vector<std::unique_ptr<GameObject>> _game_objects;
};
