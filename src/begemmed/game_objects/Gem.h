#pragma once

#include "src/engine/game_objects/AnimatedGameObject.h"

class Gem : public AnimatedGameObject {
  public:
    static const Vec2i cSize;
    static const int cNumberOfColors;

    static const char* cAnimDefault;
    static const char* cAnimFlashing;

    enum class State {
      Default,
      Hovered,
      Pressed,
      Breaking,
      ToDestroy
    };
    enum class Color {
      Beige,
      Blue,
      Green,
      Orange,
      Pink
    };

    Gem(Vec2f pos, Color gem_color);

    Color getColor() const;
    State getState() const;
    bool isMoving() const;

    void moveTo(Vec2f delta_pos);
    void moveFrom(Vec2f delta_pos);
    bool setState(State new_gem_state);

    virtual void update(int delta_time) override;

  private:
    static const char* cPath;
    static const float cAcceleration;

    static const char* cAnimHovered;
    static const char* cAnimPressed;
    static const char* cAnimBreaking;
    static const char* cAnimToDestroy;

    static const std::map<std::string, AnimationData> generateAnimationData(Color gem_color);
    static const std::map<Color, std::map<std::string, AnimationData>> cAnimsData;

    Vec2f _to_move {};
    Vec2f _v {};

    Color _gem_color;
    State _gem_state {State::Default};
};
