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
    int streamIndex = -1;                         //音频流索引
    AVCodecParameters *codec_par;                 //解码参数
    AVCodecContext *codecContext = NULL;          //解码器上下文

public:
    Audio();
    ~Audio();
};

#endif //AUDIOSDK_AUDIO_H
