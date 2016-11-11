//
// Created by kason_zhang on 11/11/2016.
//
#include "jniutils_JniBase.h"
// 引入log头文件
#include <android/log.h>
// log标签
#define TAG "hello_load"
// 定义info信息
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
// 定义debug信息
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
// 定义error信息
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

JNIEXPORT jstring JNICALL Java_jniutils_JniBase_testDataBseType
  (JNIEnv * env, jobject thiz, jboolean boo, jbyte b, jchar c, jshort s, jint i, jlong l,
  jfloat f, jdouble d){
    unsigned char c_jboolean = boo;
    char c_jbyte = b;
    unsigned short c_jchar = c;
    short c_jshort = s;
    int c_jint = i;
    long c_jlong = l;
    float c_jfloat = f;
    double c_jdouble = d;
    LOGI("DATA is %c,%c",c_jboolean,b);
    char *p = "hello,world";
    jstring re = (*env)->NewStringUTF(env,p);
    //if(re == NULL)
    return re;
  }
