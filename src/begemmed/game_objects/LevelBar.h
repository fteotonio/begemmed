#pragma once

#include "src/engine/game_objects/ui/StaticImage.h"

class LevelBar : public GameObject {
  public:
    explicit LevelBar(Vec2f pos);

    void setProgress(float percentage);

  private:
    static const char* cLevelBarProgressPath;
    static const Vec2i cLevelBarProgressSize;

    static const Vec2i cLevelBarPosOffset;
    static const int cLevelBarMaxHeight;

    StaticImage* createProgress(float percentage);
};
