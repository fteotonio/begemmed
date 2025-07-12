#include "Timer.h"

#include <iostream>
#include <cmath>

Timer::Timer(int milliseconds, bool start_now) {
  _time_to_pass = milliseconds;
  _is_running   = start_now;
}

bool Timer::isRunning() const {
  return _is_running;
}

bool Timer::hasEnded() const {
  return (_is_running && _time_passed > _time_to_pass);
}

void Timer::startTimer() {
  _is_running = true;
}

void Timer::pauseTimer() {
  _is_running = false;
}

void Timer::resetTimer() {
  _time_passed = 0;
  _is_running  = true;
}

void Timer::resetTimer(int milliseconds) {
  _time_to_pass = milliseconds;
  _time_passed  = 0;
  _is_running   = true;
}

void Timer::update(int delta_time) {
  if (_is_running && _time_passed <= _time_to_pass) {
    _time_passed += delta_time;
  }
}

Timer::operator std::string() const {
  int seconds_left  = static_cast<int>(ceil((_time_to_pass - _time_passed) / 1000.0));
  int minutes_left  = seconds_left / 60;
  seconds_left     -= minutes_left * 60;
  std::string ret {std::to_string(minutes_left) + (seconds_left < 10 ? ":0" : ":") + std::to_string(seconds_left)};
  return ret;
}

std::ostream& operator<<(std::ostream& os, const Timer& timer) {
  os << std::string(timer);
  return os;
}
