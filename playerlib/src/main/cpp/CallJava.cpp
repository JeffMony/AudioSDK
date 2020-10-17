//
// Created by jeffmony on 20-10-17.
//

#include "CallJava.h"

CallJava::CallJava(JavaVM *vm, JNIEnv *env, jobject *jobj) {
    this->vm = vm;
    this->env = env;
    this->jobj = env->NewGlobalRef(*jobj);

    jclass  jcls = env->GetObjectClass(*jobj);
    if (!jcls) {
        LOGE("Get jclass failed");
        return;
    }
    jmid_prepared = env->GetMethodID(jcls, "onPrepared", "()V");
}

void CallJava::onCallPrepared(int thread_type) {
    if (thread_type == MAIN_THREAD) {
        env->CallVoidMethod(jobj, jmid_prepared);
    } else if (thread_type == CHILD_THREAD) {
        JNIEnv* jniEnv;
        if (vm->AttachCurrentThread(&jniEnv, 0) != JNI_OK) {
            LOGE("Get child thread jnienv failed");
            return;
        }
        jniEnv->CallVoidMethod(jobj, jmid_prepared);
        vm->DetachCurrentThread();
    }
}

CallJava::~CallJava() {

}
