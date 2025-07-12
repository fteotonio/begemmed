#pragma once

#include "src/engine/game_states/GameState.h"
#include "src/engine/util/StateMachine.h"

#include <vector>

class GameStateMachine : public StateMachine<GameState> {
  public:
    void update(int delta_time);
    void render() const;
};
