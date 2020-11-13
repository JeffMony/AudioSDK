//
// Created by jeffmony on 20-10-17.
//

#include "Audio.h"

Audio::Audio(PlayerStatus *status) {
    status_ = status;
    queue_ = new CustomQueue(status);
}

Audio::~Audio() {

}

