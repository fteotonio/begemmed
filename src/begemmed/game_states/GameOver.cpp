#include "GameOver.h"

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

const char* GameOver::cGameOverString {"Game Over"};
const char* GameOver::cFlavorString {"Thanks for playing!"};
const char* GameOver::cScoreString {"Final Score: "};
const char* GameOver::cAgainString {"Play Again"};
const char* GameOver::cExitString {"Exit Game"};

GameOver::GameOver() {
  // Positions
  const Vec2f cGameOverTextPos {cScreenSize / 2 + Vec2i(0, -40)};
  const Vec2f cFlavorTextPos {cScreenSize / 2 + Vec2i(0, -20)};
  const Vec2f cScoreTextPos {cScreenSize / 2};
  const Vec2f cAgainButtonPos {cScreenSize / 2 + Vec2i(-cBigButtonSize.x / 2 - 55, 20)};
  const Vec2f cExitButtonPos {cScreenSize / 2 + Vec2i(-cBigButtonSize.x / 2 + 55, 20)};
  const Vec2f cAgainContentPos {cAgainButtonPos + cBigButtonSize / 2};
  const Vec2f cExitContentPos {cExitButtonPos + cBigButtonSize / 2};

  // Background
  addObject(new Background());

  // Labels
  std::string score_text = cScoreString + std::to_string(GameManager::instance()->getScore());
  addObject(new ShadowedLabel<M6x11Label>(cGameOverTextPos, cGameOverString, cFntMedium));
  addObject(new ShadowedLabel<M5x7Label>(cFlavorTextPos, cFlavorString));
  addObject(new ShadowedLabel<M5x7Label>(cScoreTextPos, score_text));

  // Play Again and Exit Buttons
  GameObject* again_text = new ShadowedLabel<M5x7Label>(cAgainContentPos, cAgainString);
  _again_button          = new BigButton(cAgainButtonPos, again_text);
  addObject(_again_button);

  GameObject* exit_text = new ShadowedLabel<M5x7Label>(cExitContentPos, cExitString);
  _exit_button          = new BigButton(cExitButtonPos, exit_text);
  addObject(_exit_button);
}

void GameOver::update(int delta_time) {
  GameState::update(delta_time);
  // Start new Game
  if (_again_button->getState() == Button::State::PressAction) {
    Game::instance()->getGameStateMachine()->changeState(new Playing());
    SoundManager::instance()->playSFX(cSoundStart);
    return;
  }
  // Leave to Main Menu
  if (_exit_button->getState() == Button::State::PressAction) {
    Game::instance()->getGameStateMachine()->changeState(new Title());
    SoundManager::instance()->playSFX(cSoundSelect);
  }
}
