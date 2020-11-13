//
// Created by jeffmony on 20-11-11.
//

#include "CustomQueue.h"

CustomQueue::CustomQueue(PlayerStatus *status) {
    pthread_mutex_init(&packetMuxtex, NULL);
    pthread_cond_init(&packetCond, NULL);
    this->status_ = status;
}

CustomQueue::~CustomQueue() {
    pthread_mutex_destroy(&packetMuxtex);
    pthread_cond_destroy(&packetCond);
}

int CustomQueue::addQueue(AVPacket *packet) {
    pthread_mutex_lock(&packetMuxtex);
    packetQueue.push(packet);
    pthread_cond_signal(&packetCond);
    pthread_mutex_unlock(&packetMuxtex);
    return 0;
}

int CustomQueue::getQueue(AVPacket *packet) {
    pthread_mutex_lock(&packetMuxtex);
    //告诉消费者当前AVPacket已经放入队列了
    while(status_ != NULL && !status_->is_exit) {
        if (packetQueue.size() > 0) {
            AVPacket *frontPacket = packetQueue.front();
            if (av_packet_ref(packet, frontPacket) == 0) {
                packetQueue.pop();
            }
            av_packet_free(&frontPacket);
            av_free(frontPacket);
            frontPacket = NULL;
            LOGE("从队列中取出一个AVPacket, 还剩下: %d", packetQueue.size());
            break;
        } else {
            //等待队列数据充满
            pthread_cond_wait(&packetCond, &packetMuxtex);
        }
    }
    pthread_mutex_unlock(&packetMuxtex);
    return 0;
}

int CustomQueue::getSize() {
    int size = 0;
    pthread_mutex_lock(&packetMuxtex);
    size = packetQueue.size();
    pthread_mutex_unlock(&packetMuxtex);
    return size;
}

