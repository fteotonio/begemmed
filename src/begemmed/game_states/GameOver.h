#pragma once

#include "src/engine/game_objects/ui/Button.h"
#include "src/engine/game_states/GameState.h"

namespace BegemmedState {
  class GameOver : public GameState {
    public:
      GameOver();

      virtual void update(int delta_time) override;

    private:
      static const char* cGameOverString;
      static const char* cFlavorString;
      static const char* cScoreString;
      static const char* cAgainString;
      static const char* cExitString;

      Button* _again_button;
      Button* _exit_button;
  };
}  // namespace BegemmedState
