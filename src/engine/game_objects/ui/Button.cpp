#include "Button.h"

#include "src/engine/input/InputHandler.h"

#include <iostream>

const char* Button::cAnimDefault {"Default"};
const char* Button::cAnimHovered {"Hovered"};
const char* Button::cAnimHovPressed {"HovPressed"};
const char* Button::cAnimUnhovPressed {"UnhovPressed"};

const std::map<std::string, AnimationData> Button::cAnimsData {
  {     cAnimDefault, AnimationData(0, 0)},
  {     cAnimHovered, AnimationData(0, 1)},
  {  cAnimHovPressed, AnimationData(0, 2)},
  {cAnimUnhovPressed, AnimationData(0, 3)}
};

Button::Button(Vec2f pos, Vec2i size, const std::string& filename) : AnimatedGameObject(pos, size, filename) {
  addAnimation(cAnimDefault, new Animation(cAnimsData.at(cAnimDefault)));
  addAnimation(cAnimHovered, new Animation(cAnimsData.at(cAnimHovered)));
  addAnimation(cAnimHovPressed, new Animation(cAnimsData.at(cAnimHovPressed)));
  addAnimation(cAnimUnhovPressed, new Animation(cAnimsData.at(cAnimUnhovPressed)));
  setAnimation(cAnimDefault, false);
}

Button::State Button::getState() const {
  return _button_state;
}

bool Button::setState(State button_state) {
  switch (button_state) {
    case State::Default: {
      if (_button_state == State::Hovered || _button_state == State::UnhovPressed || _button_state == State::Inactive || _button_state == State::PressAction) {
        _button_state = State::Default;
        setAnimation(cAnimDefault, false);
        return true;
      }
      break;
    }
    case State::Hovered: {
      if (_button_state == State::Default || _button_state == State::PressAction) {
        _button_state = State::Hovered;
        setAnimation(cAnimHovered, false);
        return true;
      }
      break;
    }
    case State::HovPressed: {
      if (_button_state == State::Hovered || _button_state == State::UnhovPressed) {
        _button_state = State::HovPressed;
        setAnimation(cAnimHovPressed, false);
        return true;
      }
      break;
    }
    // Unhovered pressed state to allow click cancelling by releasing outside range
    case State::UnhovPressed: {
      if (_button_state == State::HovPressed) {
        _button_state = State::UnhovPressed;
        setAnimation(cAnimUnhovPressed, false);
        return true;
      }
      break;
    }
    case State::PressAction: {
      if (_button_state == State::HovPressed) {
        _button_state = State::PressAction;
        return true;
      }
      break;
    }
    case State::Inactive: {
      _button_state = State::Inactive;
      setAnimation(cAnimUnhovPressed, false);
      return true;
    }
  }
  std::cerr << "Illegal Button Transition from " << int(_button_state) << " to " << int(button_state) << "\n";
  return false;
}

void Button::update(int delta_time) {
  handleInput();
  AnimatedGameObject::update(delta_time);
}

void Button::handleInput() {
  int mouseX = InputHandler::instance()->getMouseX();
  int mouseY = InputHandler::instance()->getMouseY();
  bool is_hovering =
    mouseX > _pos.x && mouseX < _pos.x + _dst_size.x && mouseY > _pos.y && mouseY < _pos.y + _dst_size.y;
  bool is_clicking = InputHandler::instance()->getMouseLeft();

  // Handling State Transitions
  if (_button_state == State::PressAction) {
    if (is_hovering) {
      setState(State::Hovered);
    } else {
      setState(State::Default);
    }
  }
  if (is_hovering) {
    if (is_clicking) {
      if (_button_state == State::Hovered) {
        setState(State::HovPressed);
      } else if (_button_state == State::UnhovPressed) {
        setState(State::HovPressed);
      }
    } else {
      if (_button_state == State::HovPressed) {
        setState(State::PressAction);
      }
      if (_button_state == State::Default) {
        setState(State::Hovered);
      }
    }
  } else {
    if (is_clicking) {
      if (_button_state == State::HovPressed) {
        setState(State::UnhovPressed);
      }
    } else {
      if (_button_state == State::UnhovPressed) {
        setState(State::Default);
      }
      if (_button_state == State::Hovered) {
        setState(State::Default);
      }
    }
  }
}
