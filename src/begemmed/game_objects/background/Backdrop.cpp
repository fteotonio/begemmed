#include "Backdrop.h"

#include "src/begemmed/BegemmedDisplay.h"

using namespace BegemmedDisplay;

const Vec2i Backdrop::cSize {cScreenSize + Vec2i(cTotalSteps, 0)};
const char* Backdrop::cPath {"res/images/backdrop.png"};

const int Backdrop::cTotalSteps {16};
const int Backdrop::cTimePerStep {60};

const char* Backdrop::cAnimDefault {"Default"};
const std::map<std::string, AnimationData> Backdrop::cAnimsData = {
  {cAnimDefault, AnimationData(0, 0)}
};

int Backdrop::_steps {0};
Timer Backdrop::_step_timer {Timer(cTimePerStep, true)};

Backdrop::Backdrop() : AnimatedGameObject(Vec2f(-cTotalSteps + _steps, 0), cSize, cPath) {
  addAnimation(cAnimDefault, new Animation(cAnimsData.at(cAnimDefault)));
  setAnimation(cAnimDefault, true);
}

void Backdrop::update(int delta_time) {
  AnimatedGameObject::update(delta_time);
  _step_timer.update(delta_time);

  if (_step_timer.hasEnded()) {
    ++_steps;
    // Last step is the same as first one
    if (_steps == cTotalSteps) {
      _steps = 0;
    }
    _step_timer.resetTimer();
  }
  // Pos is set to ensure correct value after a GameState is popped
  _pos.x = -cTotalSteps + _steps;
}
