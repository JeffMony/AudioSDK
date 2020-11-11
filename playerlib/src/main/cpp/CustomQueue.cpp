//
// Created by jeffmony on 20-11-11.
//

#include "CustomQueue.h"

CustomQueue::CustomQueue() {
    pthread_mutex_init(&packetMuxtex, NULL);
    pthread_cond_init(&packetCond, NULL);
}

CustomQueue::~CustomQueue() {
    pthread_mutex_destroy(&packetMuxtex);
    pthread_cond_destroy(&packetCond);
}

int CustomQueue::addQueue(AVPacket *packet) {
    pthread_mutex_lock(&packetMuxtex);
    packetQueue.push(packet);
    //告诉消费者当前AVPacket已经放入队列了
    pthread_cond_signal(&packetCond);
    pthread_mutex_unlock(&packetMuxtex);
    return 0;
}

int CustomQueue::getQueue(AVPacket *packet) {
    pthread_mutex_lock(&packetMuxtex);
    pthread_mutex_unlock(&packetMuxtex);
    return 0;
}

