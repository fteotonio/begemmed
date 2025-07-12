#include "BegemmedSound.h"

#include "src/engine/sound/SoundManager.h"

namespace BegemmedSound {
  void loadAllSound() {
    // load Music
    SoundManager::instance()->load(cMusicGame);

    // load SFX
    SoundManager::instance()->load(cSoundBreak);
    SoundManager::instance()->load(cSoundBreak2);
    SoundManager::instance()->load(cSoundBreak3);
    SoundManager::instance()->load(cSoundBreak4);
    SoundManager::instance()->load(cSoundLevelUp);
    SoundManager::instance()->load(cSoundLose);
    SoundManager::instance()->load(cSoundSwap);
    SoundManager::instance()->load(cSoundSelect);
    SoundManager::instance()->load(cSoundStart);
  }
}  // namespace BegemmedSound
