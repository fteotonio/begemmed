#pragma once

#include <memory>
#include <vector>

template<typename T>
class StateMachine {
  public:
    virtual bool isEmpty() {
      return _states.empty();
    }

    virtual void pushState(T* state) {
      _states.push_back(std::unique_ptr<T>(state));
    }

    virtual void changeState(T* state) {
      while (!_states.empty()) {
        _states.pop_back();
      }
      pushState(state);
    }

    virtual void popState() {
      if (!_states.empty()) {
        _states.pop_back();
      }
    }

    virtual ~StateMachine() {
      while (!_states.empty()) {
        StateMachine<T>::popState();
      }
    }

  protected:
    std::vector<std::unique_ptr<T>> _states;
};
