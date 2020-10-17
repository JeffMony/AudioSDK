//
// Created by jeffmony on 20-10-17.
//

#ifndef AUDIOSDK_AUDIO_H
#define AUDIOSDK_AUDIO_H

extern "C" {
#include "libavcodec/avcodec.h"
};

class Audio {
public:
    int streamIndex = -1;
    AVCodecParameters *codec_par;
    AVCodecContext *codecContext = NULL;

public:
    Audio();
    ~Audio();
};

#endif //AUDIOSDK_AUDIO_H
