#pragma once

#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>

class TextureManager {
  public:
    static TextureManager* instance();

    static std::string
      getTextKey(const std::string& filename, const int size, const std::string& text, const SDL_Color color);
    static std::string getFontKey(const std::string& filename, const int size);

    SDL_Texture* loadTexture(const std::string& filename);
    SDL_Texture* loadText(const std::string& filename, int size, const std::string& text, SDL_Color color);

    void addUsage(const std::string& texture_key);
    void removeUsage(const std::string& texture_key);

    void draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) const;

    ~TextureManager();

  private:
    static TextureManager* _texture_manager;

    static const bool cDebug {false};
    static int _loaded_textures;

    std::map<std::string, SDL_Texture*> _textures;
    std::map<std::string, TTF_Font*> _fonts;
    std::map<std::string, int> _usage_counter;

    TTF_Font* loadFont(const std::string& filename, int size);

    void releaseTextures(std::map<std::string, SDL_Texture*>& textures);
    void releaseFonts();
};
