#pragma once

#include "src/engine/game_objects/AnimatedGameObject.h"
#include "src/engine/util/Timer.h"

class Backdrop : public AnimatedGameObject {
  public:
    Backdrop();

    virtual void update(int delta_time) override;

  private:
    static const Vec2i cSize;
    static const char* cPath;

    static const int cTotalSteps;
    static const int cTimePerStep;

    static const char* cAnimDefault;
    static const std::map<std::string, AnimationData> cAnimsData;

    // Static to keep consistency between Game States
    static int _steps;
    static Timer _step_timer;
};
