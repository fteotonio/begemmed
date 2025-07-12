#pragma once

#include "src/engine/game_objects/AnimationData.h"

class Animation {
  public:
    explicit Animation(const AnimationData& anim_data) :
    _anim_data(&anim_data), _current_frame(_anim_data->_first_frame) {};

    bool isPlaying() const;
    int getFrameRow() const;
    int getLastFrame() const;
    int getCurrentFrame() const;
    bool hasPlayedOnce() const;

    void setCurrentFrame(int frame);
    void play();

    void update(int delta_time);

  private:
    const AnimationData* _anim_data;

    int _current_frame;
    int _time_passed {0};
    bool _is_playing {false};
};
