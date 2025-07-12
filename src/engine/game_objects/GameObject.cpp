#include "GameObject.h"

int GameObject::_obj_counter {0};

Vec2f GameObject::getPos() const {
  return _pos;
}

void GameObject::setPos(Vec2f pos) {
  _pos = pos;
}

void GameObject::update(int delta_time) {
  for (auto& obj: _children) {
    obj->update(delta_time);
  }
}

void GameObject::render() const {
  for (auto& obj: _children) {
    obj->render();
  }
}

void GameObject::addChild(GameObject* child) {
  child->setPos(_pos + child->getPos());
  _children.push_back(std::unique_ptr<GameObject>(child));
}