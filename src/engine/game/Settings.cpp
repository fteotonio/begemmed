#include "Settings.h"

Settings* Settings::_settings {nullptr};

Settings* Settings::instance() {
  if (!_settings) {
    _settings = new Settings();
  }
  return _settings;
}

void Settings::init(int screen_w, int screen_h, int game_scale) {
  Settings::instance()->_screen_w = screen_w;
  Settings::instance()->_screen_h = screen_h;
  setGameScale(game_scale);
}

int Settings::getScreenW() {
  return Settings::instance()->_screen_w;
}

int Settings::getScreenH() {
  return Settings::instance()->_screen_h;
}

int Settings::getGameScale() {
  return Settings::instance()->_game_scale;
}

void Settings::setGameScale(int game_scale) {
  Settings::instance()->_game_scale = game_scale;
}
