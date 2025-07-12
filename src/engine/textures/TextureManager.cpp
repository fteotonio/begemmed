#include "TextureManager.h"

#include "src/engine/game/Game.h"

#include <iostream>

TextureManager* TextureManager::_texture_manager {nullptr};

int TextureManager::_loaded_textures {0};

TextureManager* TextureManager::instance() {
  if (!_texture_manager) {
    _texture_manager = new TextureManager();
  }
  return _texture_manager;
}

std::string TextureManager::getTextKey(
  const std::string& filename,
  const int size,
  const std::string& text,
  const SDL_Color color
) {
  return filename + ':' + std::to_string(size) + ':' + text + ':' + std::to_string(color.r) + ':' +
         std::to_string(color.g) + ':' + std::to_string(color.b);
}

std::string TextureManager::getFontKey(const std::string& filename, const int size) {
  return filename + ':' + std::to_string(size);
}

SDL_Texture* TextureManager::loadTexture(const std::string& filename) {
  std::map<std::string, SDL_Texture*>::iterator find_result = _textures.find(filename);

  if (find_result == _textures.end()) {
    SDL_Surface* temp_surface = IMG_Load(filename.c_str());
    if (!temp_surface) {
      std::cerr << "Image could not be loaded: " << SDL_GetError() << std::endl;
      return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::instance()->getRenderer(), temp_surface);
    if (cDebug) {
      std::cout << "Loaded Texture: " << ++_loaded_textures << " (" << filename << ")" << std::endl;
    }
    SDL_FreeSurface(temp_surface);

    _usage_counter.insert({filename, 0});
    _textures.insert({filename, texture});
    return texture;
  }
  return find_result->second;
}

SDL_Texture* TextureManager::loadText(const std::string& filename, int size, const std::string& text, SDL_Color color) {
  std::string text_key = getTextKey(filename, size, text, color);
  TTF_Font* font       = loadFont(filename, size);

  std::map<std::string, SDL_Texture*>::iterator find_result = _textures.find(text_key);

  if (find_result == _textures.end()) {
    SDL_Surface* temp_surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture      = SDL_CreateTextureFromSurface(Game::instance()->getRenderer(), temp_surface);
    SDL_FreeSurface(temp_surface);
    if (cDebug) {
      std::cout << "Loaded Texture: " << ++_loaded_textures << " (" << text_key << ")" << std::endl;
    }
    _usage_counter.insert({text_key, 0});
    _textures.insert({text_key, texture});
    return texture;
  } else {
    return find_result->second;
  }
}

void TextureManager::addUsage(const std::string& texture_key) {
  ++(_usage_counter.at(texture_key));
}

void TextureManager::removeUsage(const std::string& texture_key) {
  --(_usage_counter.at(texture_key));
  if (_usage_counter.at(texture_key) == 0) {
    _usage_counter.erase(texture_key);
    if (cDebug) {
      std::cout << "Destroyed Texture " << --_loaded_textures << " (" << texture_key << ")" << std::endl;
    }
    SDL_DestroyTexture(_textures.at(texture_key));
    _textures.erase(texture_key);
  }
}

void TextureManager::draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) const {
  SDL_RenderCopy(Game::instance()->getRenderer(), tex, &src, &dest);
}

TextureManager::~TextureManager() {
  releaseTextures(_textures);
  releaseFonts();
}

TTF_Font* TextureManager::loadFont(const std::string& filename, int size) {
  std::string font_key = getFontKey(filename, size);

  std::map<std::string, TTF_Font*>::iterator find_result = _fonts.find(font_key);

  if (find_result == _fonts.end()) {
    TTF_Font* font = TTF_OpenFont(filename.c_str(), size);
    if (!font) {
      std::cerr << "Font could not be loaded: " << SDL_GetError() << std::endl;
      return nullptr;
    }
    _fonts.insert({font_key, font});
    return font;
  }
  return find_result->second;
}

void TextureManager::releaseTextures(std::map<std::string, SDL_Texture*>& textures) {
  std::map<std::string, SDL_Texture*>::iterator it = textures.begin();
  while (it != textures.end()) {
    if (it->second != NULL) {
      if (cDebug) {
        std::cout << "Destroyed Texture " << --_loaded_textures << std::endl;
      }
      SDL_DestroyTexture(it->second);
      it = textures.erase(it);
    }
  }
}

void TextureManager::releaseFonts() {
  std::map<std::string, TTF_Font*>::iterator it = _fonts.begin();
  while (it != _fonts.end()) {
    if (it->second != NULL) {
      TTF_CloseFont(it->second);
      it = _fonts.erase(it);
    }
  }
}
