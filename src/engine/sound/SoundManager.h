#pragma once

#include "src/engine/sound/Sound.h"

#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>

class SoundManager {
  public:
    static SoundManager* instance();

    void load(Sound sound);
    void playMusic(Sound music, int loops) const;
    void stopMusic() const;
    void setMusicVolume(int volume) const;
    void playSFX(Sound sfx) const;
    void setSFXVolume(std::string id, int volume) const;

    ~SoundManager();

  private:
    static const int cAudioFrequency {66150};
    static const int cAudioChannelNumber {2};
    static const int cAudioChunkSize {4096};

    static SoundManager* _sound_manager;

    std::map<std::string, Mix_Music*> _musics;
    std::map<std::string, Mix_Chunk*> _sfxs;
};
