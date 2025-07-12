#pragma once

struct AnimationData {
    AnimationData(int first_frame, int last_frame, int frame_row, int ms_per_frame) :
    _first_frame(first_frame), _last_frame(last_frame), _frame_row(frame_row), _ms_per_frame(ms_per_frame) {};

    AnimationData(int only_frame, int frame_row) : AnimationData(only_frame, only_frame, frame_row, 0) {};

    int _first_frame;
    int _last_frame;
    int _frame_row;
    int _ms_per_frame;
};
