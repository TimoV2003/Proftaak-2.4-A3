#pragma once

#include <string>
#include "bass.h"

class AudioPlayer {
public:
    AudioPlayer();
    ~AudioPlayer();

    bool load(const std::string& filePath);
    void play();
    void stop();

private:
    HSTREAM stream_;
    bool initialized_;
};
