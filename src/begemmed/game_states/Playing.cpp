#include "Playing.h"

#include "src/begemmed/BegemmedDisplay.h"
#include "src/begemmed/BegemmedSound.h"
#include "src/begemmed/GameManager.h"
#include "src/begemmed/game_objects/Gem.h"
#include "src/begemmed/game_objects/LevelBar.h"
#include "src/begemmed/game_objects/background/Background.h"
#include "src/begemmed/game_objects/ui/BegemmedButtons.h"
#include "src/begemmed/game_objects/ui/BegemmedImages.h"
#include "src/begemmed/game_objects/ui/BegemmedText.h"
#include "src/begemmed/game_states/GameOver.h"
#include "src/begemmed/game_states/Pause.h"
#include "src/begemmed/game_states/StateCommon.h"
#include "src/engine/game/Game.h"
#include "src/engine/sound/SoundManager.h"

using namespace BegemmedDisplay;
using namespace BegemmedSound;
using namespace BegemmedState;
using namespace BegemmedUI;

const int Playing::cBoardWidth {8};
const int Playing::cBoardHeight {8};
const char* Playing::cHintString {"Hint?"};
const int Playing::cEndGameTimerValue {500};
const int Playing::cGameTime {2 * 60 * 1000};

Playing::Playing() {
  // Reset values
  GameManager::instance()->resetGame();
  // Play Music
  SoundManager::instance()->playMusic(BegemmedSound::cMusicGame, -1);

  // Positions
  const Vec2f cPanelPos(SideStrip::cSize.x + 8, cScreenSize.y / 2 - cPanelSize.y / 2);
  const Vec2f cLevelBarOutlinePos {cPanelPos + Vec2i(cPanelSize.x + 13, 0)};
  const Vec2f cScoreTextPos {cPanelPos + Vec2i(8, 6)};
  const Vec2f cScoreValuePos {cScoreTextPos + Vec2i(cPanelSize.x - 16, 11)};
  const Vec2f cLevelTextPos {cScoreValuePos + Vec2i(-cPanelSize.x + 16, 13)};
  const Vec2f cLevelValuePos {cLevelTextPos + Vec2i(cPanelSize.x - 16, 11)};
  const Vec2f cTimeTextPos {cLevelValuePos + Vec2i(-cPanelSize.x + 16, 13)};
  const Vec2f cTimeValuePos {cTimeTextPos + Vec2i(cPanelSize.x - 16, 11)};

  const Vec2f cHintButtonPos {
    cPanelPos + Vec2i((cPanelSize.x - cMediumButtonSize.x) / 2, cPanelSize.y - cMediumButtonSize.y - 8)};
  const Vec2f cHintContentPos {cHintButtonPos + cMediumButtonSize / 2};

  const Vec2f cBoardPos(
    cScreenSize.x - SideStrip::cSize.x - cBoardWidth * Gem::cSize.x - 8,
    (cScreenSize.y - cBoardWidth * Gem::cSize.y) / 2
  );

  // Background
  addObject(_background = new Background());

  // Panel
  addObject(new PanelImage(cPanelPos));

  // Level Bar
  _level_bar = new LevelBar(cLevelBarOutlinePos);
  addObject(_level_bar);

  // Timers
  _end_game_timer = std::make_unique<Timer>(cEndGameTimerValue, false);
  _level_timer    = std::make_unique<Timer>(cGameTime, true);

  // Board
  _board = new Board(cBoardPos, cBoardWidth, cBoardHeight);
  addObject(_board);

  // Buttons
  GameObject* icon = new PauseIcon(cSmallButtonContentPos);
  _pause_button    = new SmallButton(getTopRightButtonPos(), icon);
  addObject(_pause_button);

  GameObject* text = new ShadowedLabel<M5x7Label>(cHintContentPos, cHintString);
  _hint_button     = new MediumButton(cHintButtonPos, text);
  addObject(_hint_button);

  // Text
  addObject(new ShadowedLabel<M5x7Label>(cScoreTextPos, "Score:", cFntSmall, Text::Align::UpLeft));
  addObject(new ShadowedLabel<M5x7Label>(cLevelTextPos, "Level:", cFntSmall, Text::Align::UpLeft));
  addObject(new ShadowedLabel<M5x7Label>(cTimeTextPos, "Time:", cFntSmall, Text::Align::UpLeft));

  // Dynamic Text Elements (Handled directly by state)
  _score_value       = GameManager::instance()->getScore();
  _score_value_label = std::make_unique<ShadowedLabel<M5x7Label>>(
    cScoreValuePos,
    std::to_string(_score_value),
    cFntSmall,
    Text::Align::UpRight
  );
  _level_value       = GameManager::instance()->getLevel();
  _level_value_label = std::make_unique<ShadowedLabel<M5x7Label>>(
    cLevelValuePos,
    std::to_string(_level_value),
    cFntSmall,
    Text::Align::UpRight
  );

  _time_value = std::string(*_level_timer);
  _time_value_label =
    std::make_unique<ShadowedLabel<M5x7Label>>(cTimeValuePos, _time_value, cFntSmall, Text::Align::UpRight);
}

void Playing::update(int delta_time) {
  _end_game_timer->update(delta_time);
  _level_timer->update(delta_time);
  GameState::update(delta_time);
  updateLevelProgress();
  checkScore();
  checkLevel();
  checkButtons();
  checkTime();
}

void Playing::render() const {
  GameState::render();
  _score_value_label->render();
  _level_value_label->render();
  _time_value_label->render();
}

void Playing::updateLevelProgress() {
  int score                 = GameManager::instance()->getScore();
  int level                 = GameManager::instance()->getLevel();
  int score_to_next         = GameManager::instance()->getScoreToNextLevel(level);
  int score_to_previous     = GameManager::instance()->getScoreToNextLevel(level - 1);
  float current_level_score = score - score_to_previous;
  _level_bar->setProgress(current_level_score / (score_to_next - score_to_previous));
}

void Playing::checkScore() {
  int new_score = GameManager::instance()->getScore();
  if (_score_value == new_score) {
    return;
  }
  _score_value = new_score;
  Vec2f pos    = _score_value_label->getPos();
  _score_value_label.reset(
    new ShadowedLabel<M5x7Label>(pos, std::to_string(_score_value), cFntSmall, Text::Align::UpRight)
  );
}

void Playing::checkLevel() {
  int new_level = GameManager::instance()->getLevel();
  if (_level_value == new_level) {
    return;
  }
  _level_timer->resetTimer();
  _level_value = new_level;
  Vec2f pos    = _level_value_label->getPos();
  _level_value_label.reset(
    new ShadowedLabel<M5x7Label>(pos, std::to_string(_level_value), cFntSmall, Text::Align::UpRight)
  );

  _background->setStripState(SideStrip::State::LevelUp);
  SoundManager::instance()->playSFX(BegemmedSound::cSoundLevelUp);
}

void Playing::checkTime() {
  // End game animation has finished
  if (_end_game_timer->hasEnded()) {
    Game::instance()->getGameStateMachine()->changeState(new GameOver());
    return;
  }

  std::string new_time = std::string(*_level_timer);
  if (_time_value != new_time) {
    _time_value = new_time;
    Vec2f pos   = _time_value_label->getPos();
    _time_value_label.reset(new ShadowedLabel<M5x7Label>(pos, _time_value, cFntSmall, Text::Align::UpRight));
  }

  // Timer ran out, start end game animation
  if (_level_timer->hasEnded()) {
    _board->breakAllGems(false, true);
    SoundManager::instance()->stopMusic();
    SoundManager::instance()->playSFX(cSoundLose);
    _end_game_timer->startTimer();
  }
}

// Check for actions in all buttons
void Playing::checkButtons() {
  if (_hint_button->getState() == Button::State::PressAction) {
    _hint_button->setState(Button::State::Default);
    _board->searchHint();
    SoundManager::instance()->playSFX(cSoundSelect);
  }

  if (_pause_button->getState() == Button::State::PressAction) {
    _pause_button->setState(Button::State::Default);
    Game::instance()->getGameStateMachine()->pushState(new Pause());
    SoundManager::instance()->playSFX(cSoundSelect);
  }
}
