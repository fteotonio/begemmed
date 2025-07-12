#pragma once

#include <iostream>

class Timer {
    friend std::ostream& operator<<(std::ostream& os, const Timer& timer);

  public:
    Timer(int milliseconds, bool start_now);

    bool isRunning() const;
    bool hasEnded() const;

    void startTimer();
    void pauseTimer();
    void resetTimer();
    void resetTimer(int milliseconds);

    void update(int delta_time);

    operator std::string() const;

  private:
    bool _is_running {false};
    int _time_passed {0};
    int _time_to_pass;
};
