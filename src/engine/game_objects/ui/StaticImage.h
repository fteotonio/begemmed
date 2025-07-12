#pragma once

#include "src/engine/game_objects/AnimatedGameObject.h"

#include <string>

class StaticImage : public AnimatedGameObject {
  public:
    StaticImage(Vec2f pos, Vec2i src_size, Vec2i dst_size, const std::string& filename);
    StaticImage(Vec2f pos, Vec2i size, const std::string& filename) : StaticImage(pos, size, size, filename) {};

  private:
    static const char* cAnimDefault;

    static const std::map<std::string, AnimationData> cAnimsData;
};
