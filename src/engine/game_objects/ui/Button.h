#pragma once

#include "src/engine/game_objects/AnimatedGameObject.h"

#include <string>
#include <vector>

class Button : public AnimatedGameObject {
  public:
    enum class State {
      Default,
      Hovered,
      HovPressed,
      UnhovPressed,
      PressAction,
      Inactive
    };

    Button(Vec2f pos, Vec2i size, const std::string& filename);

    State getState() const;
    bool setState(State button_state);

    virtual void update(int delta_time) override;

  private:
    static const char* cAnimDefault;
    static const char* cAnimHovered;
    static const char* cAnimHovPressed;
    static const char* cAnimUnhovPressed;

    static const std::map<std::string, AnimationData> cAnimsData;

    State _button_state {State::Default};

    void handleInput();
};
