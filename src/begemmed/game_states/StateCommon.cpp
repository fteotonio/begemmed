#include "StateCommon.h"

#include "src/begemmed/BegemmedDisplay.h"
#include "src/begemmed/game_objects/ui/BegemmedButtons.h"

using namespace BegemmedUI;
using namespace BegemmedDisplay;

namespace BegemmedState {
  const Vec2i cSmallButtonContentPos {8, 8};

  Vec2f getTopRightButtonPos() {
    return Vec2f(cScreenSize.x - cSmallButtonSize.x - 2, 2);
  }
}  // namespace BegemmedState
