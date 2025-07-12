#include "AnimatedGameObject.h"

#include "src/engine/game/Settings.h"
#include "src/engine/textures/TextureManager.h"

Vec2i AnimatedGameObject::getSize() {
  return _dst_size;
}

void AnimatedGameObject::addAnimation(std::string id, Animation* animation) {
  _animations.insert({id, std::unique_ptr<Animation>(animation)});
}

void AnimatedGameObject::setAnimation(std::string id, bool play_now) {
  _current_anim = _animations.at(id).get();
  if (play_now) {
    _current_anim->play();
  }
}

void AnimatedGameObject::update(int delta_time) {
  _current_anim->update(delta_time);
  GameObject::update(delta_time);
}

void AnimatedGameObject::render() const {
  SDL_Rect src;
  src.x = _current_anim->getCurrentFrame() * _src_size.x;
  src.y = _current_anim->getFrameRow() * _src_size.y;
  src.w = _src_size.x;
  src.h = _src_size.y;

  SDL_Rect dest;
  // Round to Int before Scale to avoid sub-pixel movement
  dest.x = static_cast<int>(round(_pos.x)) * Settings::getGameScale();
  dest.y = static_cast<int>(round(_pos.y)) * Settings::getGameScale();
  dest.w = _dst_size.x * Settings::getGameScale();
  dest.h = _dst_size.y * Settings::getGameScale();
  TextureManager::instance()->draw(_texture, src, dest);

  GameObject::render();
}

AnimatedGameObject::~AnimatedGameObject() {
  TextureManager::instance()->removeUsage(_texture_key);
}
