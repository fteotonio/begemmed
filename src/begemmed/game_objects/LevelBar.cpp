#include "LevelBar.h"

#include "src/begemmed/game_objects/ui/BegemmedImages.h"
#include "src/engine/game_objects/ui/StaticImage.h"

using namespace BegemmedUI;

const char* LevelBar::cLevelBarProgressPath {"res/images/levelbar.png"};
const Vec2i LevelBar::cLevelBarProgressSize {8, 1};

const Vec2i LevelBar::cLevelBarPosOffset {2, 2};
const int LevelBar::cLevelBarMaxHeight {122};

LevelBar::LevelBar(Vec2f pos) : GameObject(pos) {
  addChild(createProgress(0));
  addChild(new LevelBarOutline(Vec2i(0, 0)));
}

// Remake progress image with correct height in right position
void LevelBar::setProgress(float percentage) {
  _children[0].reset(createProgress(percentage));
}

StaticImage* LevelBar::createProgress(float percentage) {
  int progress_height = cLevelBarMaxHeight * percentage;
  Vec2f progress_pos  = _pos + cLevelBarPosOffset + Vec2i(0, cLevelBarMaxHeight - progress_height);
  return new StaticImage(
    progress_pos,
    cLevelBarProgressSize,
    Vec2i(cLevelBarProgressSize.x, progress_height),
    cLevelBarProgressPath
  );
}
