#include "StaticImage.h"

const char* StaticImage::cAnimDefault {"Default"};

const std::map<std::string, AnimationData> StaticImage::cAnimsData {
  {cAnimDefault, AnimationData(0, 0)}
};

StaticImage::StaticImage(Vec2f pos, Vec2i src_size, Vec2i dst_size, const std::string& filename) :
AnimatedGameObject(pos, src_size, dst_size, filename) {
  addAnimation(cAnimDefault, new Animation(cAnimsData.at(cAnimDefault)));
  setAnimation(cAnimDefault, false);
}
