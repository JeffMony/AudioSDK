//
// Created by jeffmony on 20-10-17.
//

#ifndef AUDIOSDK_CALLJAVA_H
#define AUDIOSDK_CALLJAVA_H

#include <jni.h>
#include "androidlog.h"

#define MAIN_THREAD 0
#define CHILD_THREAD 1

class CallJava {

public:
    _JavaVM *vm = NULL;
    JNIEnv *env = NULL;
    jobject jobj;

    jmethodID  jmid_prepared;

public:
    CallJava(JavaVM *vm, JNIEnv *env, jobject *jobj);
    ~CallJava();

    void onCallPrepared(int thread_type);
};


#endif //AUDIOSDK_CALLJAVA_H
