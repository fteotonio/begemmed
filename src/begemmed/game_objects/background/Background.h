#pragma once

#include "src/begemmed/game_objects/background/Backdrop.h"
#include "src/begemmed/game_objects/background/SideStrip.h"
#include "src/engine/game_objects/GameObject.h"

class Background : public GameObject {
  public:
    Background();

    void setStripState(SideStrip::State state);

  private:
    SideStrip* _left_strip;
    SideStrip* _right_strip;
};
