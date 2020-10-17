//
// Created by jeffmony on 20-10-17.
//
#include <android/log.h>
#ifndef AUDIOSDK_ANDROIDLOG_H
#define AUDIOSDK_ANDROIDLOG_H

#define LOGV(...)   __android_log_print((int)ANDROID_LOG_VERBOSE, "NATIVEPLAYER", __VA_ARGS__)
#define LOGD(...)   __android_log_print((int)ANDROID_LOG_DEBUG, "NATIVEPLAYER", __VA_ARGS__)
#define LOGI(...)   __android_log_print((int)ANDROID_LOG_INFO, "NATIVEPLAYER", __VA_ARGS__)
#define LOGW(...)   __android_log_print((int)ANDROID_LOG_WARN, "NATIVEPLAYER", __VA_ARGS__)
#define LOGE(...)   __android_log_print((int)ANDROID_LOG_ERROR, "NATIVEPLAYER", __VA_ARGS__)

#endif //AUDIOSDK_ANDROIDLOG_H


