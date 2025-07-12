#pragma once

#include "src/engine/game_objects/ui/Text.h"
#include "src/engine/util/Colors.h"
#include "src/engine/util/Vec2.h"

namespace BegemmedUI {
  extern const std::string cM6X11;
  extern const std::string cM5X7;
  extern const int cFntSmall;
  extern const int cFntMedium;
  extern const int cFntLarge;

  // Abstractions for used Text objects inside game states.
  class M6x11Label : public Text {
    public:
      M6x11Label(
        Vec2f pos,
        const std::string& text,
        int size          = cFntSmall,
        Text::Align align = Text::Align::Mid,
        SDL_Color color   = Colors::cWhite
      ) :
      Text(pos, text, size, cM6X11, align, color) {
        // Font-specific position fix
        _pos = _pos + Vec2f(0, _size / 16);
      }
  };

  class M5x7Label : public Text {
    public:
      M5x7Label(
        Vec2f pos,
        const std::string& text,
        int size          = cFntSmall,
        Text::Align align = Text::Align::Mid,
        SDL_Color color   = Colors::cWhite
      ) :
      Text(pos, text, size, cM5X7, align, color) {
        // Font-specific position fix
        _pos = _pos - Vec2f(0, 2 * _size / 16);
      }
  };

  template<typename T>
  class ShadowedLabel : public GameObject {
    public:
      ShadowedLabel(
        Vec2f pos,
        const std::string& text,
        int size               = cFntSmall,
        Text::Align align      = Text::Align::Mid,
        SDL_Color text_color   = Colors::cWhite,
        SDL_Color shadow_color = Colors::cBlack
      ) :
      GameObject(pos) {
        addChild(new T(Vec2f(1, 1), text, size, align, shadow_color));
        addChild(new T(Vec2f(0, 0), text, size, align, text_color));
      }
  };

};  // namespace BegemmedUI
