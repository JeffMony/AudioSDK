//
// Created by jeffmony on 20-10-17.
//
#include <jni.h>
#include "androidlog.h"
#include "CallJava.h"
#include "FFmpegImpl.h"
#include "PlayerStatus.h"

JavaVM *javaVm = NULL;
CallJava *callJava = NULL;
FFmpegImpl *ffmpegImpl = NULL;
PlayerStatus *status_ = NULL;

extern "C"
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm ,void *reserved) {
    jint result = -1;
    javaVm = vm;
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }
    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeffmony_playerlib_NativePlayer_n_1prepare(JNIEnv *env, jobject jobj, jstring jurl) {
    const char *url = env->GetStringUTFChars(jurl, 0);
    if (ffmpegImpl == NULL) {
        if (callJava == NULL) {
            callJava = new CallJava(javaVm, env, &jobj);
        }
        status_ = new PlayerStatus();
        ffmpegImpl = new FFmpegImpl(callJava, url, status_);
    }
    ffmpegImpl->prepare();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jeffmony_playerlib_NativePlayer_n_1start(JNIEnv *env, jobject thiz) {
    if (ffmpegImpl != NULL) {
        ffmpegImpl->start();
    }
}
