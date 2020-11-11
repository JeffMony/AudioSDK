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

class CustomQueue {

public:
    std::queue<AVPacket *> packetQueue;
    pthread_mutex_t  packetMuxtex;
    pthread_cond_t packetCond;

public:
    CustomQueue();
    ~CustomQueue();

    int addQueue(AVPacket* packet);

    int getQueue(AVPacket* packet);
};



#endif //AUDIOSDK_CUSTOMQUEUE_H
