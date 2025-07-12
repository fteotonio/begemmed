#pragma once

#include <SDL2/SDL.h>

class InputHandler {
  public:
    static InputHandler* instance();

    bool getMouseLeftPress() const;
    bool getMouseLeftRelease() const;
    bool getMouseLeft() const;
    Sint32 getMouseX() const;
    Sint32 getMouseY() const;

    void update();

  private:
    static InputHandler* _input_handler;

    bool _mouse_left_press {false};
    bool _mouse_left_release {false};
    bool _mouse_left_hold {false};
    Sint32 _mouse_x {0};
    Sint32 _mouse_y {0};
};
