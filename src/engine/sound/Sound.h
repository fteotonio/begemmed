#pragma once

#include <string>

struct Sound {
    enum class Type {
      Music,
      SFX
    };

    Sound(const std::string& new_id, const std::string& new_path, Type new_type, int new_volume) :
    id(new_id), path(new_path), type(new_type), volume(new_volume) {};

    const std::string id;
    const std::string path;
    const Type type;
    const int volume;
};
