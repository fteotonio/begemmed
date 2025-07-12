#pragma once

#include "src/begemmed/BegemmedDisplay.h"
#include "src/engine/game_objects/AnimatedGameObject.h"

using namespace BegemmedDisplay;

class SideStrip : public AnimatedGameObject {
  public:
    enum class State {
      Default,
      LevelUp
    };

    static const Vec2i cSize;

    explicit SideStrip(Vec2f pos);

    bool setState(State new_state);

    virtual void update(int delta_time) override;

  private:
    static const char* cPath;
    static const Vec2i cSrcSize;

    static const char* cAnimDefault;
    static const char* cAnimLevelUp;
    static const std::map<std::string, AnimationData> cAnimsData;

    State _state {State::Default};
};
