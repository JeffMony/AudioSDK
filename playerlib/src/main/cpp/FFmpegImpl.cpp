//
// Created by jeffmony on 20-10-17.
//

#include "FFmpegImpl.h"

FFmpegImpl::FFmpegImpl(CallJava *callJava, const char *url) {
    this->callJava = callJava;
    this->url = url;
}

FFmpegImpl::~FFmpegImpl() {

}

void *decodeFFmpeg(void *data) {
    FFmpegImpl *ffmpeg = (FFmpegImpl *)data;
    ffmpeg->decodeFFmpegThread();
    pthread_exit(&ffmpeg->decodeThread);
}

void FFmpegImpl::prepare() {
    pthread_create(&decodeThread, NULL, decodeFFmpeg, this);
}

void FFmpegImpl::decodeFFmpegThread() {
    av_register_all();
    avformat_network_init();

    pFmt = avformat_alloc_context();
    if (avformat_open_input(&pFmt, url, NULL, NULL) != 0) {
        LOGE("Cannot open url = %s", url);
        return;
    }
    if (avformat_find_stream_info(pFmt, NULL) < 0) {
        LOGE("Cannot find stream,  url = %s", url);
        return;
    }
    for (int i = 0; i < pFmt->nb_streams; i++) {
        if (pFmt->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            if (audio == NULL) {
                audio = new Audio();
                audio->streamIndex = i;
            }
        }
    }



}
