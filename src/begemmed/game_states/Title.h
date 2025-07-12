#pragma once

#include "src/engine/game_objects/ui/Button.h"
#include "src/engine/game_states/GameState.h"

namespace BegemmedState {
  class Title : public GameState {
    public:
      Title();

      virtual void update(int delta_time) override;

    private:
      static const char* cStartString;

      Button* _play_button {nullptr};
      Button* _exit_button {nullptr};
  };
}  // namespace BegemmedState
