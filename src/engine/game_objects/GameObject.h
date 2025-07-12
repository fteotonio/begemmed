#pragma once

#include "src/engine/util/Vec2.h"

#include <iostream>
#include <memory>
#include <vector>

class GameObject {
  public:
    explicit GameObject(Vec2f pos) : _pos(pos) {
      if (cDebug) {
        std::cout << "Created Object: " << ++_obj_counter << std::endl;
      }
    }

    GameObject() : GameObject({0, 0}) {}

    virtual void update(int delta_time);
    virtual void render() const;

    virtual Vec2f getPos() const;
    virtual void setPos(Vec2f pos);

    virtual ~GameObject() {
      if (cDebug) {
        std::cout << "Destroyed Object: " << --_obj_counter << std::endl;
      }
    }

  protected:
    Vec2f _pos;
    std::vector<std::unique_ptr<GameObject>> _children;

    void addChild(GameObject* child);

  private:
    static const bool cDebug {false};
    static int _obj_counter;
};
