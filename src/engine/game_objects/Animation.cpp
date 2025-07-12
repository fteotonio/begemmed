#include "Animation.h"

bool Animation::isPlaying() const {
  return _is_playing;
}

int Animation::getFrameRow() const {
  return _anim_data->_frame_row;
}

int Animation::getLastFrame() const {
  return _anim_data->_last_frame;
}

int Animation::getCurrentFrame() const {
  return _current_frame;
}

// Returns true if last frame was reached at least once.
bool Animation::hasPlayedOnce() const {
  if (_is_playing && _anim_data->_ms_per_frame > 0) {
    int frames_completed = _time_passed / _anim_data->_ms_per_frame;
    int last_frame       = _anim_data->_last_frame - _anim_data->_first_frame;
    return frames_completed >= last_frame;
  }
  return false;
}

void Animation::setCurrentFrame(int frame) {
  _current_frame = frame;
}

void Animation::play() {
  _time_passed = 0;
  _is_playing  = true;
}

void Animation::update(int delta_time) {
  if (_is_playing && _anim_data->_ms_per_frame > 0) {
    _time_passed     += delta_time;
    int total_frames  = _anim_data->_last_frame - _anim_data->_first_frame + 1;
    int total_time    = total_frames * _anim_data->_ms_per_frame;
    if (_time_passed > total_time) {
      _time_passed -= total_time;
    }
    int frames_completed = _time_passed / _anim_data->_ms_per_frame;
    _current_frame       = _anim_data->_first_frame + frames_completed % total_frames;
  }
}
