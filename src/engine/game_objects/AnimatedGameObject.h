#pragma once

#include "src/engine/game_objects/Animation.h"
#include "src/engine/game_objects/GameObject.h"
#include "src/engine/textures/TextureManager.h"

#include <SDL2/SDL_image.h>
#include <map>
#include <memory>
#include <string>

class AnimatedGameObject : public GameObject {
  public:
    explicit AnimatedGameObject() :
    GameObject(), _texture_key(""), _src_size({0, 0}), _dst_size({0, 0}), _texture(nullptr) {}

    explicit AnimatedGameObject(Vec2f pos, Vec2i src_size, Vec2i dst_size, const std::string& texture_path) :
    GameObject(pos),
    _texture_key(texture_path),
    _src_size(src_size),
    _dst_size(dst_size),
    _texture(TextureManager::instance()->loadTexture(texture_path)) {
      TextureManager::instance()->addUsage(texture_path);
    }

    explicit AnimatedGameObject(Vec2f pos, Vec2i size, const std::string& texture_path) :
    AnimatedGameObject(pos, size, size, texture_path) {}

    Vec2i getSize();

    void addAnimation(std::string id, Animation* animation);
    void setAnimation(std::string id, bool play_now);

    virtual void update(int delta_time) override;
    virtual void render() const override;

    virtual ~AnimatedGameObject();

  protected:
    std::string _texture_key;

    Vec2i _src_size;
    Vec2i _dst_size;

    SDL_Texture* _texture {nullptr};
    Animation* _current_anim {nullptr};
    std::map<std::string, std::unique_ptr<Animation>> _animations;
};
