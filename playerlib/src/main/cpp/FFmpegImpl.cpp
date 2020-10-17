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
                audio->codec_par = pFmt->streams[i]->codecpar;

            }
        }
    }

    AVCodec *decode = avcodec_find_decoder(audio->codec_par->codec_id);
    if (!decode) {
        LOGE("Cannot get decoder, %d", audio->codec_par->codec_id);
        return;
    }

    audio->codecContext = avcodec_alloc_context3(decode);
    if (!audio->codecContext) {
        LOGE("Cannot alloc avcodec context");
        return;
    }
    int ret = avcodec_parameters_to_context(audio->codecContext, audio->codec_par);
    if (ret < 0) {
        LOGE("Cannot fill context to decoder");
        return;
    }
    if (avcodec_open2(audio->codecContext, decode, 0) != 0) {
        LOGE("Cannot open audio stream");
        return;
    }
    callJava->onCallPrepared(CHILD_THREAD);

}

void FFmpegImpl::start() {
    if (audio == NULL) {
        LOGE("audio is null");
        return;
    }
    int count = 0;
    while(1) {
        AVPacket *packet = av_packet_alloc();
        if (av_read_frame(pFmt, packet) == 0) {
            if (packet->stream_index == audio->streamIndex) {
                count++;
                LOGI("解码第 %d 帧", count);



                av_packet_free(&packet);
                av_free(packet);
                packet = NULL;
            }
        } else {
            LOGE("av_read_frame failed or end");
            av_packet_free(&packet);
            av_free(packet);
            packet = NULL;
            break;
        }
    }
}
