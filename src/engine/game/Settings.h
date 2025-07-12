#pragma once

class Settings {
  public:
    static Settings* instance();

    static void init(int screen_w, int screen_h, int game_scale = 1);

    static int getScreenW();
    static int getScreenH();
    static int getGameScale();
    static void setGameScale(int game_scale);

  private:
    int _screen_w {};
    int _screen_h {};
    int _game_scale {};

    static Settings* _settings;
};
