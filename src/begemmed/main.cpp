#include "src/begemmed/BegemmedDisplay.h"
#include "src/begemmed/BegemmedSound.h"
#include "src/begemmed/GameManager.h"
#include "src/begemmed/game_states/Title.h"
#include "src/engine/game/Game.h"
#include "src/engine/game/Settings.h"
#include "src/engine/sound/Sound.h"
#include "src/engine/sound/SoundManager.h"

using namespace BegemmedDisplay;
using namespace BegemmedSound;
using namespace BegemmedState;

int main(int argc, char *argv[]) {
  const int frame_delay = 1000 / cTargetFPS;

  Uint32 frame_start      = SDL_GetTicks();
  Uint32 last_frame_start = SDL_GetTicks();

  Settings::instance()->init(cScreenSize.x, cScreenSize.y, cInitialGameScale);
  if (Game::instance()->init("Begemmed")) {
    GameManager::instance();
    loadAllSound();
    Game::instance()->getGameStateMachine()->pushState(new Title());
    while (Game::instance()->isGameRunning()) {
      frame_start    = SDL_GetTicks();
      int delta_time = frame_start - last_frame_start;

      Game::instance()->handleEvents();
      Game::instance()->update(delta_time);
      Game::instance()->render();

      int frame_time = SDL_GetTicks() - frame_start;
      if (frame_delay > frame_time) {
        SDL_Delay(frame_delay - frame_time);
      }
      last_frame_start = frame_start;
    }
    delete Game::instance();
    delete GameManager::instance();
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}
