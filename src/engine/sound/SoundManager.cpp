#include "SoundManager.h"

#include <iostream>

SoundManager* SoundManager::_sound_manager {nullptr};

SoundManager* SoundManager::instance() {
  if (!_sound_manager) {
    _sound_manager = new SoundManager();
    Mix_OpenAudio(cAudioFrequency, AUDIO_S16, cAudioChannelNumber, cAudioChunkSize);
  }
  return _sound_manager;
}

void SoundManager::load(Sound sound) {
  if (sound.type == Sound::Type::Music) {
    Mix_Music* music = Mix_LoadMUS(sound.path.c_str());
    if (music) {
      _musics.insert({sound.id, music});
    } else {
      std::cerr << "Music could not be loaded: " << SDL_GetError() << std::endl;
    }
  } else if (sound.type == Sound::Type::SFX) {
    Mix_Chunk* sfx = Mix_LoadWAV(sound.path.c_str());
    if (sfx) {
      _sfxs.insert({sound.id, sfx});
      setSFXVolume(sound.id, sound.volume);
    } else {
      std::cerr << "SFX could not be loaded: " << SDL_GetError() << std::endl;
    }
  }
}

void SoundManager::playMusic(Sound music, int loops) const {
  Mix_PlayMusic(_musics.at(music.id), loops);
  setMusicVolume(music.volume);
}

void SoundManager::stopMusic() const {
  Mix_HaltMusic();
}

void SoundManager::setMusicVolume(int volume) const {
  Mix_VolumeMusic(volume);
}

void SoundManager::playSFX(Sound sfx) const {
  Mix_PlayChannel(-1, _sfxs.at(sfx.id), false);
}

void SoundManager::setSFXVolume(std::string id, int volume) const {
  Mix_VolumeChunk(_sfxs.at(id), volume);
}

SoundManager::~SoundManager() {
  Mix_CloseAudio();
}
