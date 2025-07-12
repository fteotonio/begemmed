#pragma once

#include "src/engine/game_states/GameStateMachine.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Game {
  public:
    static Game* instance();

    bool isGameRunning();
    GameStateMachine* getGameStateMachine();
    SDL_Renderer* getRenderer();

    void setWindowSize(int width, int height);

    bool init(const char* title);
    void handleEvents();
    void update(int delta_time);
    void render() const;
    void quit();

    ~Game();

  private:
    static Game* _game_instance;

    int _width {};
    int _height {};

    bool _is_game_running {false};

    GameStateMachine* _game_state_machine {nullptr};
    SDL_Window* _window {nullptr};
    SDL_Renderer* _renderer {nullptr};

    void checkWindowSize();
};
