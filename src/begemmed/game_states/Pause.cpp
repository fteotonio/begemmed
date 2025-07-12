#include "Pause.h"

#include "src/begemmed/BegemmedDisplay.h"
#include "src/begemmed/BegemmedSound.h"
#include "src/begemmed/GameManager.h"
#include "src/begemmed/game_objects/background/Background.h"
#include "src/begemmed/game_objects/ui/BegemmedButtons.h"
#include "src/begemmed/game_objects/ui/BegemmedImages.h"
#include "src/begemmed/game_objects/ui/BegemmedText.h"
#include "src/begemmed/game_states/Playing.h"
#include "src/begemmed/game_states/StateCommon.h"
#include "src/begemmed/game_states/Title.h"
#include "src/engine/game/Game.h"
#include "src/engine/sound/SoundManager.h"

using namespace BegemmedDisplay;
using namespace BegemmedSound;
using namespace BegemmedState;
using namespace BegemmedUI;

const char* Pause::cPausedString {"Game Paused"};
const char* Pause::cFlavorString {"Time for a break."};
const char* Pause::cScoreString {"Current Score: "};
const char* Pause::cResumeString {"Resume"};
const char* Pause::cExitString {"Exit Game"};

Pause::Pause() {
  // Positions
  const Vec2f cPausedTextPos {cScreenSize / 2 + Vec2i(0, -40)};
  const Vec2f cFlavorTextPos {cScreenSize / 2 + Vec2i(0, -20)};
  const Vec2f cScoreTextPos {cScreenSize / 2};
  const Vec2f cResumeButtonPos {cScreenSize / 2 + Vec2i(-cBigButtonSize.x / 2 - 55, 20)};
  const Vec2f cExitButtonPos {cScreenSize / 2 + Vec2i(-cBigButtonSize.x / 2 + 55, 20)};
  const Vec2f cResumeContentPos {cResumeButtonPos + cBigButtonSize / 2};
  const Vec2f cExitContentPos {cExitButtonPos + cBigButtonSize / 2};

  // Background
  addObject(new Background());

  // Labels
  std::string score_text = cScoreString + std::to_string(GameManager::instance()->getScore());
  addObject(new ShadowedLabel<M6x11Label>(cPausedTextPos, cPausedString, cFntMedium));
  addObject(new ShadowedLabel<M5x7Label>(cFlavorTextPos, cFlavorString));
  addObject(new ShadowedLabel<M5x7Label>(cScoreTextPos, score_text));

  // Resume and Exit Buttons
  GameObject* resume_text = new ShadowedLabel<M5x7Label>(cResumeContentPos, cResumeString);
  _resume_button          = new BigButton(cResumeButtonPos, resume_text);
  addObject(_resume_button);

  GameObject* exit_text = new ShadowedLabel<M5x7Label>(cExitContentPos, cExitString);
  _exit_button          = new BigButton(cExitButtonPos, exit_text);
  addObject(_exit_button);
}

void Pause::update(int delta_time) {
  GameState::update(delta_time);
  // Back to Game
  if (_resume_button->getState() == Button::State::PressAction) {
    Game::instance()->getGameStateMachine()->popState();
    SoundManager::instance()->playSFX(cSoundSelect);
    return;
  }
  // Exit to Menu
  if (_exit_button->getState() == Button::State::PressAction) {
    SoundManager::instance()->stopMusic();
    Game::instance()->getGameStateMachine()->changeState(new Title());
    SoundManager::instance()->playSFX(cSoundSelect);
  }
}
