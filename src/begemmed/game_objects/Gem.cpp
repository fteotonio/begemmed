#include "Gem.h"

#include <cmath>
#include <iostream>

const char* Gem::cPath {"res/images/gems.png"};
const Vec2i Gem::cSize {16, 16};
const float Gem::cAcceleration {0.45f / 1000};  // increase speed by 0.45 pixels per s.
const int Gem::cNumberOfColors {5};

const char* Gem::cAnimDefault   = "Default";
const char* Gem::cAnimHovered   = "Hovered";
const char* Gem::cAnimPressed   = "Pressed";
const char* Gem::cAnimBreaking  = "Breaking";
const char* Gem::cAnimToDestroy = "ToDestroy";
const char* Gem::cAnimFlashing  = "Flashing";

const std::map<std::string, AnimationData> Gem::generateAnimationData(Color gem_color) {
  int frame_row = static_cast<int>(gem_color);
  return {
    {cAnimDefault, AnimationData(1, frame_row)},
    {cAnimHovered, AnimationData(0, frame_row)},
    {cAnimPressed, AnimationData(7, frame_row)},
    {cAnimBreaking, AnimationData(1, 6, frame_row, 40)},
    {cAnimToDestroy, AnimationData(6, frame_row)},
    {cAnimFlashing, AnimationData(0, 1, frame_row, 300)}
  };
}

const std::map<Gem::Color, std::map<std::string, AnimationData>> Gem::cAnimsData {
  { Color::Beige,  Gem::generateAnimationData(Color::Beige)},
  {  Color::Blue,   Gem::generateAnimationData(Color::Blue)},
  { Color::Green,  Gem::generateAnimationData(Color::Green)},
  {Color::Orange, Gem::generateAnimationData(Color::Orange)},
  {  Color::Pink,   Gem::generateAnimationData(Color::Pink)}
};

Gem::Gem(Vec2f pos, Color gem_color) : AnimatedGameObject(pos, cSize, cPath), _gem_color(gem_color) {
  addAnimation(cAnimDefault, new Animation(cAnimsData.at(_gem_color).at(cAnimDefault)));
  addAnimation(cAnimHovered, new Animation(cAnimsData.at(_gem_color).at(cAnimHovered)));
  addAnimation(cAnimPressed, new Animation(cAnimsData.at(_gem_color).at(cAnimPressed)));
  addAnimation(cAnimBreaking, new Animation(cAnimsData.at(_gem_color).at(cAnimBreaking)));
  addAnimation(cAnimToDestroy, new Animation(cAnimsData.at(_gem_color).at(cAnimToDestroy)));
  addAnimation(cAnimFlashing, new Animation(cAnimsData.at(_gem_color).at(cAnimFlashing)));
  setAnimation(cAnimDefault, false);
}

Gem::Color Gem::getColor() const {
  return _gem_color;
}

Gem::State Gem::getState() const {
  return _gem_state;
}

// Returns true if Gem hasn't finished moving
bool Gem::isMoving() const {
  return _to_move.dist() > 0;
}

// Sets movement target to pos + delta_pos
void Gem::moveTo(Vec2f delta_pos) {
  _to_move += delta_pos;
}

// Moves gem instantly to pos + delta_pos, and sets move target to original position
void Gem::moveFrom(Vec2f delta_pos) {
  _pos += delta_pos;
  moveTo(-delta_pos);
}

bool Gem::setState(State new_gem_state) {
  switch (new_gem_state) {
    case State::Default: {
      if (_gem_state == State::Hovered || _gem_state == State::Pressed) {
        _gem_state = new_gem_state;
        setAnimation(cAnimDefault, false);
        return true;
      }
      break;
    }
    case State::Hovered: {
      if (_gem_state == State::Default || _gem_state == State::Pressed) {
        _gem_state = new_gem_state;
        setAnimation(cAnimHovered, false);
        return true;
      }
      break;
    }
    case State::Pressed: {
      if (_gem_state == State::Hovered) {
        _gem_state = new_gem_state;
        setAnimation(cAnimPressed, false);
        return true;
      }
      break;
    }
    case State::Breaking: {
      if (_gem_state == State::Default || _gem_state == State::Hovered || _gem_state == State::Pressed) {
        _gem_state = new_gem_state;
        setAnimation(cAnimBreaking, true);
        return true;
      }
      break;
    }
    case State::ToDestroy: {
      _gem_state = new_gem_state;
      setAnimation(cAnimToDestroy, false);
      return true;
    }
  }
  std::cerr << "Illegal State Transition from " << int(_gem_state) << " to " << int(new_gem_state) << "\n";
  return false;
}

void Gem::update(int delta_time) {
  // Calculate amount to move in this frame.
  Vec2f move_unit = {_v.x * delta_time, _v.y * delta_time};

  if (_to_move.x != 0) {
    if (abs(_to_move.x) < abs(move_unit.x)) {
      _pos.x     += _to_move.x;
      _to_move.x  = 0;
      _v.x        = 0;
    } else {
      _pos.x     += move_unit.x;
      _to_move.x -= move_unit.x;
      _v.x       += copysign(cAcceleration, _to_move.x) * delta_time;
    }
  }
  if (_to_move.y != 0) {
    if (abs(_to_move.y) < abs(move_unit.y)) {
      _pos.y     += _to_move.y;
      _to_move.y  = 0;
      _v.y        = 0;
    } else {
      _pos.y     += move_unit.y;
      _to_move.y -= move_unit.y;
      _v.y       += copysign(cAcceleration, _to_move.y) * delta_time;
    }
  }

  // Check if gem should be destroyed
  if (_current_anim->hasPlayedOnce() && _gem_state == State::Breaking) {
    setState(State::ToDestroy);
  }

  AnimatedGameObject::update(delta_time);
}
