//
// Created by jeffmony on 20-10-17.
//
#include <jni.h>
#include "androidlog.h"
#include "CallJava.h"
#include "FFmpegImpl.h"

JavaVM *javaVm = NULL;
CallJava *callJava = NULL;
FFmpegImpl *ffmpegImpl = NULL;

extern "C"
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm ,void *reserved) {
    jint result = -1;
    javaVm = vm;
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(env), JNI_VERSION_1_6) != JNI_OK) {
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
        ffmpegImpl = new FFmpegImpl(callJava, url);
    }
    ffmpegImpl->prepare();

    env->ReleaseStringUTFChars(jurl, url);
}
