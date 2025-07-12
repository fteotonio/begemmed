#pragma once

#include "src/engine/game_objects/ui/Button.h"
#include "src/engine/util/Vec2.h"

// Sizes and image paths for all button sizes
namespace BegemmedUI {
  extern const Vec2i cSmallButtonSize;
  extern const Vec2i cMediumButtonSize;
  extern const Vec2i cBigButtonSize;

  extern const char* cSmallButtonPath;
  extern const char* cMediumButtonPath;
  extern const char* cBigButtonPath;

  class SmallButton : public Button {
    public:
      SmallButton(Vec2f pos, GameObject* content) : Button(pos, cSmallButtonSize, cSmallButtonPath) {
        addChild(content);
      }
  };

  class MediumButton : public Button {
    public:
      MediumButton(Vec2f pos, GameObject* content) : Button(pos, cMediumButtonSize, cMediumButtonPath) {
        addChild(content);
      }
  };

  class BigButton : public Button {
    public:
      BigButton(Vec2f pos, GameObject* content) : Button(pos, cBigButtonSize, cBigButtonPath) {
        addChild(content);
      }
  };
}  // namespace BegemmedUI
