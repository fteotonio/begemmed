#include "InputHandler.h"

#include "src/engine/game/Game.h"
#include "src/engine/game/Settings.h"

InputHandler* InputHandler::_input_handler {nullptr};

InputHandler* InputHandler::instance() {
  if (!_input_handler) {
    _input_handler = new InputHandler();
  }
  return _input_handler;
}

bool InputHandler::getMouseLeftPress() const {
  return _mouse_left_press;
}

bool InputHandler::getMouseLeftRelease() const {
  return _mouse_left_release;
}

bool InputHandler::getMouseLeft() const {
  return _mouse_left_hold;
}

Sint32 InputHandler::getMouseX() const {
  return _mouse_x / Settings::getGameScale();
}

Sint32 InputHandler::getMouseY() const {
  return _mouse_y / Settings::getGameScale();
}

void InputHandler::update() {
  SDL_Event event;

  _mouse_left_release = false;
  _mouse_left_press   = false;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
          _mouse_left_hold  = true;
          _mouse_left_press = true;
        }
        break;
      case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT) {
          _mouse_left_hold    = false;
          _mouse_left_release = true;
        }
        break;
      case SDL_MOUSEMOTION:
        _mouse_x = event.motion.x;
        _mouse_y = event.motion.y;
        break;
      case SDL_QUIT: Game::instance()->quit(); break;
      default: break;
    }
  }
}
