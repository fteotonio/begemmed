#pragma once

#include "src/engine/game_objects/ui/StaticImage.h"
#include "src/engine/util/Vec2.h"

// Sizes and image paths for all non-moving images
namespace BegemmedUI {
  extern const Vec2i cSmallIconSize;
  extern const Vec2i cTitleSize;
  extern const Vec2i cPanelSize;
  extern const Vec2i cLevelBarOutlineSize;

  extern const char* cPauseIconPath;
  extern const char* cExitIconPath;
  extern const char* cTitlePath;
  extern const char* cPanelPath;
  extern const char* cLevelBarOutlinePath;

  class PauseIcon : public StaticImage {
    public:
      explicit PauseIcon(Vec2f pos) : StaticImage(pos, cSmallIconSize, cPauseIconPath) {}
  };

  class ExitIcon : public StaticImage {
    public:
      explicit ExitIcon(Vec2f pos) : StaticImage(pos, cSmallIconSize, cExitIconPath) {}
  };

  class TitleImage : public StaticImage {
    public:
      explicit TitleImage(Vec2f pos) : StaticImage(pos, cTitleSize, cTitlePath) {}
  };

  class PanelImage : public StaticImage {
    public:
      explicit PanelImage(Vec2f pos) : StaticImage(pos, cPanelSize, cPanelPath) {}
  };

  class LevelBarOutline : public StaticImage {
    public:
      explicit LevelBarOutline(Vec2f pos) : StaticImage(pos, cLevelBarOutlineSize, cLevelBarOutlinePath) {}
  };
}  // namespace BegemmedUI
