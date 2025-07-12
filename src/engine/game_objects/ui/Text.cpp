#include "Text.h"

#include "src/engine/textures/TextureManager.h"

const char* Text::cAnimDefault = "Default";

const std::map<std::string, AnimationData> Text::cAnimsData {
  {cAnimDefault, AnimationData(0, 0)}
};

Text::Text(Vec2f pos, const std::string& text, int size, const std::string& font, Align align, SDL_Color color) :
AnimatedGameObject(), _size(size) {
  _texture_key = TextureManager::getTextKey(font, size, text, color);
  _texture     = TextureManager::instance()->loadText(font, size, text, color);

  TextureManager::instance()->addUsage(_texture_key);

  int w, h;
  SDL_QueryTexture(_texture, NULL, NULL, &w, &h);
  _src_size = _dst_size = Vec2i(w, h);

  float x {0};
  float y {0};
  // Offset real position from arguments to align text
  switch (align) {
    case Align::UpLeft: {
      x = pos.x;
      y = pos.y;
      break;
    }
    case Align::Up: {
      x = pos.x - w / 2;
      y = pos.y;
      break;
    }
    case Align::UpRight: {
      x = pos.x - w;
      y = pos.y;
      break;
    }
    case Align::MidLeft: {
      x = pos.x;
      y = pos.y - h / 2;
      break;
    }
    case Align::Mid: {
      x = pos.x - w / 2;
      y = pos.y - h / 2;
      break;
    }
    case Align::MidRight: {
      x = pos.x - w;
      y = pos.y - h / 2;
      break;
    }
    case Align::DownLeft: {
      x = pos.x;
      y = pos.y - h;
      break;
    }
    case Align::Down: {
      x = pos.x - w / 2;
      y = pos.y - h;
      break;
    }
    case Align::DownRight: {
      x = pos.x - w;
      y = pos.y - h;
      break;
    }
  }

  _pos = Vec2f(x, y);

  addAnimation(cAnimDefault, new Animation(cAnimsData.at(cAnimDefault)));
  setAnimation(cAnimDefault, false);
}
