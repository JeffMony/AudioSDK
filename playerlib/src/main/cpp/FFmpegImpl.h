//
// Created by jeffmony on 20-10-17.
//

#ifndef AUDIOSDK_FFMPEGIMPL_H
#define AUDIOSDK_FFMPEGIMPL_H

#include "CallJava.h"
#include "pthread.h"
#include "Audio.h"
#include "PlayerStatus.h"

extern "C" {
#include "libavformat/avformat.h"
};

class FFmpegImpl {
public:
    CallJava *callJava = NULL;
    const char *url = NULL;
    pthread_t  decodeThread;

    AVFormatContext *pFmt = NULL;
    Audio *audio = NULL;
    PlayerStatus *status_ = NULL;

public:
    FFmpegImpl(CallJava *callJava, const char *url, PlayerStatus *status);
    ~FFmpegImpl();

    void prepare();
    void decodeFFmpegThread();
    void start();
};

#endif //AUDIOSDK_FFMPEGIMPL_H
