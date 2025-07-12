#pragma once

#include "src/begemmed/game_objects/Board.h"
#include "src/begemmed/game_objects/LevelBar.h"
#include "src/begemmed/game_objects/background/Background.h"
#include "src/begemmed/game_objects/ui/BegemmedText.h"
#include "src/engine/game_objects/ui/Button.h"
#include "src/engine/game_states/GameState.h"

using namespace BegemmedUI;

namespace BegemmedState {
  class Playing : public GameState {
    public:
      Playing();

      virtual void update(int delta_time) override;
      virtual void render() const override;

    private:
      static const int cBoardWidth;
      static const int cBoardHeight;
      static const char* cHintString;
      static const int cEndGameTimerValue;
      static const int cGameTime;

      std::unique_ptr<Timer> _level_timer;
      std::unique_ptr<Timer> _end_game_timer;

      Background* _background;
      LevelBar* _level_bar;

      Board* _board;

      Button* _pause_button;
      Button* _hint_button;

      int _score_value;
      int _level_value;
      std::string _time_value;
      std::unique_ptr<ShadowedLabel<M5x7Label>> _score_value_label;
      std::unique_ptr<ShadowedLabel<M5x7Label>> _level_value_label;
      std::unique_ptr<ShadowedLabel<M5x7Label>> _time_value_label;

      void updateLevelProgress();

      void checkScore();
      void checkLevel();
      void checkTime();
      void checkButtons();
  };
}  // namespace BegemmedState
