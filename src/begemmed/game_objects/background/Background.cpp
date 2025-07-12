#include "Background.h"

#include "src/begemmed/BegemmedDisplay.h"
#include "src/begemmed/game_objects/background/Backdrop.h"
#include "src/begemmed/game_objects/background/SideStrip.h"
#include "src/engine/game_objects/GameObject.h"

using namespace BegemmedDisplay;

Background::Background() : GameObject() {
  const Vec2f cLeftStripPos {0, 0};
  const Vec2f cRightStripPos(cScreenSize.x - SideStrip::cSize.x, 0);

  addChild(new Backdrop());
  addChild(_left_strip = new SideStrip(cLeftStripPos));
  addChild(_right_strip = new SideStrip(cRightStripPos));
}

void Background::setStripState(SideStrip::State state) {
  _left_strip->setState(state);
  _right_strip->setState(state);
}
