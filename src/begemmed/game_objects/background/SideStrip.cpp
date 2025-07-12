#include "SideStrip.h"

#include <iostream>

const char* SideStrip::cPath {"res/images/sidestrip.png"};
const Vec2i SideStrip::cSrcSize {28, 1};
const Vec2i SideStrip::cSize {28, cScreenSize.y};

const char* SideStrip::cAnimDefault {"Default"};
const char* SideStrip::cAnimLevelUp {"LevelUp"};

const std::map<std::string, AnimationData> SideStrip::cAnimsData {
  {cAnimDefault, AnimationData(0, 0)},
  {cAnimLevelUp, AnimationData(0, 16, 0, 30)}
};

SideStrip::SideStrip(Vec2f pos) : AnimatedGameObject(pos, cSrcSize, cSize, cPath) {
  addAnimation(cAnimDefault, new Animation(cAnimsData.at(cAnimDefault)));
  addAnimation(cAnimLevelUp, new Animation(cAnimsData.at(cAnimLevelUp)));
  setAnimation(cAnimDefault, false);
}

void SideStrip::update(int delta_time) {
  AnimatedGameObject::update(delta_time);

  if (_state == State::LevelUp && _current_anim->hasPlayedOnce()) {
    setState(State::Default);
  }
}

bool SideStrip::setState(State new_state) {
  switch (new_state) {
    case State::Default: {
      if (_state == State::LevelUp) {
        _state = new_state;
        setAnimation(cAnimDefault, false);
        return true;
      }
      break;
    }
    case State::LevelUp: {
      if (_state == State::Default) {
        _state = new_state;
        setAnimation(cAnimLevelUp, true);
        return true;
      }
      break;
    }
  }
  std::cerr << "Illegal State Transition from " << int(_state) << " to " << int(new_state) << "\n";
  return false;
}
