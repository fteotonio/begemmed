#include "Game.h"

#include "src/engine/game/Settings.h"
#include "src/engine/input/InputHandler.h"
#include "src/engine/sound/SoundManager.h"
#include "src/engine/textures/TextureManager.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

Game* Game::_game_instance {nullptr};

Game* Game::instance() {
  if (!_game_instance) {
    _game_instance = new Game();
  }
  return _game_instance;
}

bool Game::isGameRunning() {
  return _is_game_running;
}

GameStateMachine* Game::getGameStateMachine() {
  return _game_state_machine;
}

SDL_Renderer* Game::getRenderer() {
  return _renderer;
}

void Game::setWindowSize(int width, int height) {
  SDL_SetWindowSize(_window, width, height);
  _width  = width;
  _height = height;
}

bool Game::init(const char* title) {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    _width  = Settings::getScreenW() * Settings::getGameScale();
    _height = Settings::getScreenH() * Settings::getGameScale();
    _window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);
    if (_window) {
      _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
      if (!_renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
      }
    } else {
      std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
      return false;
    }
    _is_game_running = true;

    TextureManager::instance();
    if (TTF_Init() != 0) {
      std::cerr << "TTF init failed: " << SDL_GetError() << std::endl;
      return false;
    }

    InputHandler::instance();
    SoundManager::instance();

    _game_state_machine = new GameStateMachine();

    return true;
  }
  std::cerr << "SDL_Init failed.\n";
  return false;
}

void Game::handleEvents() {
  InputHandler::instance()->update();
}

void Game::update(int delta_time) {
  _game_state_machine->update(delta_time);
  checkWindowSize();
}

void Game::render() const {
  SDL_RenderClear(_renderer);
  _game_state_machine->render();
  SDL_RenderPresent(_renderer);
}

void Game::quit() {
  _is_game_running = false;
}

Game::~Game() {
  delete _game_state_machine;

  delete TextureManager::instance();
  delete InputHandler::instance();
  delete SoundManager::instance();

  SDL_DestroyWindow(_window);
  SDL_DestroyRenderer(_renderer);
  TTF_Quit();
  SDL_Quit();
}

void Game::checkWindowSize() {
  int screen_w   = Settings::getScreenW();
  int screen_h   = Settings::getScreenH();
  int game_scale = Settings::getGameScale();
  if (_width != screen_w * game_scale) {
    SDL_SetWindowSize(_window, screen_w * game_scale, screen_h * game_scale);
  }
}