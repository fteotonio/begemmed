#include "GameStateMachine.h"

void GameStateMachine::update(int delta_time) {
  if (!_states.empty()) {
    _states.back()->update(delta_time);
  }
}

void GameStateMachine::render() const {
  if (!_states.empty()) {
    _states.back()->render();
  }
}
