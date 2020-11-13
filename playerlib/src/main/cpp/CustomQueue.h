//
// Created by jeffmony on 20-11-11.
//

#ifndef AUDIOSDK_CUSTOMQUEUE_H
#define AUDIOSDK_CUSTOMQUEUE_H

extern "C" {
#include "libavcodec/avcodec.h"
};

#include "pthread.h"
#include "queue"
#include "PlayerStatus.h"
#include "androidlog.h"

class CustomQueue {

public:
    std::queue<AVPacket *> packetQueue;
    pthread_mutex_t  packetMuxtex;
    pthread_cond_t packetCond;
    PlayerStatus *status_ = NULL;

public:
    CustomQueue(PlayerStatus *status);
    ~CustomQueue();

    int addQueue(AVPacket* packet);

    int getQueue(AVPacket* packet);

    int getSize();
};



#endif //AUDIOSDK_CUSTOMQUEUE_H
