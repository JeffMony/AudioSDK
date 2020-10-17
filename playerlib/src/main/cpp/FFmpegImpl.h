//
// Created by jeffmony on 20-10-17.
//

#ifndef AUDIOSDK_FFMPEGIMPL_H
#define AUDIOSDK_FFMPEGIMPL_H

#include "CallJava.h"
#include "pthread.h"
#include "Audio.h"

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

public:
    FFmpegImpl(CallJava *callJava, const char *url);
    ~FFmpegImpl();

    void prepare();
    void decodeFFmpegThread();
};

#endif //AUDIOSDK_FFMPEGIMPL_H
