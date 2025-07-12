#pragma once

#include "src/engine/game_objects/AnimatedGameObject.h"

class Text : public AnimatedGameObject {
  public:
    enum class Align {
      UpLeft,
      Up,
      UpRight,
      MidLeft,
      Mid,
      MidRight,
      DownLeft,
      Down,
      DownRight
    };

    Text(Vec2f pos, const std::string& text, int size, const std::string& font, Align align, SDL_Color color);

  protected:
    const int _size;

  private:
    static const char* cAnimDefault;

    static const std::map<std::string, AnimationData> cAnimsData;
};
