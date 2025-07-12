#include "Title.h"

#include "src/begemmed/BegemmedDisplay.h"
#include "src/begemmed/BegemmedSound.h"
#include "src/begemmed/game_objects/background/Background.h"
#include "src/begemmed/game_objects/ui/BegemmedButtons.h"
#include "src/begemmed/game_objects/ui/BegemmedImages.h"
#include "src/begemmed/game_objects/ui/BegemmedText.h"
#include "src/begemmed/game_states/Playing.h"
#include "src/begemmed/game_states/StateCommon.h"
#include "src/engine/game/Game.h"
#include "src/engine/game_objects/ui/StaticImage.h"
#include "src/engine/sound/SoundManager.h"

using namespace BegemmedDisplay;
using namespace BegemmedSound;
using namespace BegemmedState;
using namespace BegemmedUI;

const char* Title::cStartString {"Start Game!"};

Title::Title() {
  // Positions
  const Vec2f cTitlePos(cScreenSize.x / 2 - cTitleSize.x / 2, 40);

  const Vec2f cStartButtonPos {cScreenSize / 2 + Vec2i(-cBigButtonSize.x / 2, 20)};
  const Vec2f cStartContentPos {cStartButtonPos + cBigButtonSize / 2};

  // Background
  addObject(new Background());

  // Title Image
  addObject(new TitleImage(cTitlePos));

  // Start Button
  GameObject* text = new ShadowedLabel<M5x7Label>(cStartContentPos, cStartString);
  _play_button     = new BigButton(cStartButtonPos, text);
  addObject(_play_button);

  // Exit Button
  GameObject* icon = new ExitIcon(cSmallButtonContentPos);
  _exit_button     = new SmallButton(getTopRightButtonPos(), icon);
  addObject(_exit_button);
}

void Title::update(int delta_time) {
  GameState::update(delta_time);

  if (_play_button->getState() == Button::State::PressAction) {
    Game::instance()->getGameStateMachine()->changeState(new Playing());
    SoundManager::instance()->playSFX(cSoundStart);
  } else if (_exit_button->getState() == Button::State::PressAction) {
    Game::instance()->quit();
  }
}
