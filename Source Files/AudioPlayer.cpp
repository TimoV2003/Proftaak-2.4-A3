#include "AudioPlayer.h"
#include <iostream>

AudioPlayer::AudioPlayer() : stream_(0), initialized_(false) {
    if (BASS_Init(-1, 44100, 0, 0, NULL)) {
        initialized_ = true;
    }
    else {
        std::cerr << "BASS initialization failed!" << std::endl;
    }
}

AudioPlayer::~AudioPlayer() {
    if (stream_ != 0) {
        BASS_StreamFree(stream_);
    }

    if (initialized_) {
        BASS_Free();
    }
}

bool AudioPlayer::load(const std::string& filePath) {
    if (!initialized_) return false;

    if (stream_ != 0) {
        BASS_StreamFree(stream_);
        stream_ = 0;
    }

    stream_ = BASS_StreamCreateFile(FALSE, filePath.c_str(), 0, 0, 0);
    if (!stream_) {
        std::cerr << "Failed to load audio file: " << filePath << std::endl;
        return false;
    }

    return true;
}

void AudioPlayer::play() {
    if (stream_ != 0) {
        BASS_ChannelPlay(stream_, FALSE);
    }
}

void AudioPlayer::stop() {
    if (stream_ != 0) {
        BASS_ChannelStop(stream_);
    }
}
