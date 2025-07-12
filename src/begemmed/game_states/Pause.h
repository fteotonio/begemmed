#pragma once

#include "src/engine/game_objects/ui/Button.h"
#include "src/engine/game_states/GameState.h"

namespace BegemmedState {
  class Pause : public GameState {
    public:
      Pause();

      virtual void update(int delta_time) override;

    private:
      static const char* cPausedString;
      static const char* cFlavorString;
      static const char* cScoreString;
      static const char* cResumeString;
      static const char* cExitString;

      Button* _resume_button;
      Button* _exit_button;
  };
}  // namespace BegemmedState
