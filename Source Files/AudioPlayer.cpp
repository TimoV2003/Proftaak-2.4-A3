#include "AudioPlayer.h"
#include <iostream>
#include <bass.h>

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
    if (!initialized_) {
        std::cerr << "BASS not initialized.\n";
        return false;
    }

    std::cout << "Loading file: " << filePath << std::endl;

    if (stream_ != 0) {
        BASS_StreamFree(stream_);
        stream_ = 0;
    }

    stream_ = BASS_StreamCreateFile(FALSE, filePath.c_str(), 0, 0, BASS_SAMPLE_LOOP);
    if (!stream_) {
        int err = BASS_ErrorGetCode();
        std::cerr << "Failed to load audio file: " << filePath
            << "\nBASS error code: " << err << std::endl;
        return false;
    }

    return true;
}


void AudioPlayer::play() {
    if (stream_ != 0) {
        BASS_ChannelPlay(stream_, TRUE);
    }
}

void AudioPlayer::stop() {
    if (stream_ != 0) {
        BASS_ChannelStop(stream_);
    }
}
