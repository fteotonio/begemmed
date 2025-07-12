#pragma once

#include "src/engine/sound/Sound.h"
#include "src/engine/sound/SoundManager.h"

namespace BegemmedSound {
  const Sound cMusicGame {"Game", "res/sounds/game.ogg", Sound::Type::Music, 16};
  const Sound cSoundBreak {"Break", "res/sounds/break.wav", Sound::Type::SFX, 16};
  const Sound cSoundBreak2 {"Break2", "res/sounds/break2.wav", Sound::Type::SFX, 16};
  const Sound cSoundBreak3 {"Break3", "res/sounds/break3.wav", Sound::Type::SFX, 16};
  const Sound cSoundBreak4 {"Break4", "res/sounds/break4.wav", Sound::Type::SFX, 16};
  const Sound cSoundLevelUp {"LevelUp", "res/sounds/levelup.wav", Sound::Type::SFX, 20};
  const Sound cSoundLose {"Lose", "res/sounds/lose.wav", Sound::Type::SFX, 16};
  const Sound cSoundSwap {"Swap", "res/sounds/swap.wav", Sound::Type::SFX, 16};
  const Sound cSoundSelect {"Select", "res/sounds/select.wav", Sound::Type::SFX, 16};
  const Sound cSoundStart {"Start", "res/sounds/start.wav", Sound::Type::SFX, 24};

  void loadAllSound();
}  // namespace BegemmedSound
