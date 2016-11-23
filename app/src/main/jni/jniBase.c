//
// Created by kason_zhang on 11/11/2016.
//
#include "jniutils_JniBase.h"
#include <string.h>
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
JNIEXPORT void JNICALL Java_jniutils_JniBase_javeToC
        (JNIEnv *env, jobject thiz, jstring str){
    const char *getStringFromJava = (*env)->GetStringUTFChars(env,str,NULL);
    LOGI("get string from Java: %s",getStringFromJava);
    (*env)->ReleaseStringUTFChars(env,str,getStringFromJava);
}

JNIEXPORT jbyte JNICALL Java_jniutils_JniBase_getByte
        (JNIEnv * env, jobject thiz){
    char b = 127;
    jbyte re = b;
    return re;
}

JNIEXPORT jshort JNICALL Java_jniutils_JniBase_getShort
        (JNIEnv * env, jobject thiz){
    short s = 290;
    jshort re = s;
    return re;
}

JNIEXPORT jboolean JNICALL Java_jniutils_JniBase_getBoolean
        (JNIEnv * env, jobject thiz){
    unsigned char s = 255;
    jboolean re = s;
    return re;
}
//获取ArrayList对象
JNIEXPORT jobject JNICALL Java_jniutils_JniBase_getPersons
        (JNIEnv * env, jobject thiz){
    jclass c_arraylist_class = (*env)->FindClass(env,"java/util/ArrayList");//获取ArrayList的class

    jmethodID mid_arraylist_init = (*env)->GetMethodID(env,c_arraylist_class,"<init>","()V");//无参构造函数
    jobject c_arraylist_object = (*env)->NewObject(env,c_arraylist_class,mid_arraylist_init);//构造一个ArraylIst对象
    //获取ArrayList的add方法
    jmethodID c_arraylist_add = (*env)->GetMethodID(env,c_arraylist_class,"add","(Ljava/lang/Object;)Z");
    //获取Person的class
    jclass c_person_class = (*env)->FindClass(env,"entity/Person");//获取entity包下的Person class
    //获取构造函数
    jmethodID mid_person_init = (*env)->GetMethodID(env,c_person_class,"<init>","(Ljava/lang/String;I)V");

    int i = 0;
    for(i=0;i<5;i++){
        jstring person_name = (*env)->NewStringUTF(env,"Person");
        //获取person对象
        jobject c_person_object = (*env)->NewObject(env,c_person_class,mid_person_init,person_name,i*10);
        (*env)->CallBooleanMethod(env,c_arraylist_object,c_arraylist_add,c_person_object);
    }
    return c_arraylist_object;
}

JNIEXPORT void JNICALL Java_jniutils_JniBase_setJavaIn
        (JNIEnv *env, jobject thiz){

    LOGI("IN HERE");
    char *c_string = "I am String from C languange";
    jstring to_java_string= (*env)->NewStringUTF(env,"I am String from C languange");
    LOGI("to_java_string is %s",c_string);

    //1,获取class
    jclass cls = (*env)->GetObjectClass(env,thiz);

    //3,获取实力的属性ID
    jfieldID fid = (*env)->GetFieldID(env,cls,"javaIn","Ljava/lang/String;");
    if(fid == NULL){
        LOGE("null point");
        return;
    }
    //4,获取实例的属性
    //jstring jstr = (*env)->GetObjectField(env,thiz,fid);
    jstring jstr = (*env)->NewStringUTF(env,"I am String from C languange");
    (*env)->SetObjectField(env,thiz,fid,jstr);

}
/**
 * C 访问 JAVA 静态成员变量
 */
JNIEXPORT void JNICALL Java_jniutils_JniBase_accessStaticField
        (JNIEnv *env, jobject thiz){
    //1,获取class
    jclass cls = (*env)->GetObjectClass(env,thiz);
    //2,获取FieldId
    jfieldID fid = (*env)->GetStaticFieldID(env,cls,"staticString","Ljava/lang/String;");
    //3,get
    jstring jstr = (*env)->GetStaticObjectField(env,cls,fid);
    const char* c_str = (*env)->GetStringUTFChars(env,jstr,NULL);
    char * cc_str = (char*)c_str;
    LOGI("static string from java: %s",cc_str);
    (*env)->ReleaseStringUTFChars(env,jstr,c_str);
    //4,set
    jstr = (*env)->NewStringUTF(env,"12345");
    (*env)->SetStaticObjectField(env,cls,fid,jstr);
}

/**
 * C 访问 Java里的方法，回调Java
 */
JNIEXPORT void JNICALL Java_jniutils_JniBase_accessJavaMethod
        (JNIEnv *env, jobject thiz){
    //获取class
    jclass cls = (*env)->GetObjectClass(env,thiz);
    //获取methodId
    jmethodID mid = (*env)->GetMethodID(env,cls,"cVisitJavaMethod","(ILjava/lang/String;)V");
    if(mid == 0){
        LOGE("method not exist");
        return;
    }
    jstring jstr = (*env)->NewStringUTF(env,"c call java method");
    //调用
    (*env)->CallVoidMethod(env,thiz,mid,1,jstr);

}
/**
 * C 访问 Java里的静态方法；
 */
JNIEXPORT void JNICALL Java_jniutils_JniBase_accessJavaStaticMethod
        (JNIEnv *env, jobject thiz){
    jclass cls = (*env)->GetObjectClass(env,thiz);

    jmethodID mid = (*env)->GetStaticMethodID(env,cls
            ,"cVisitJavaStaticMethod","(ILjava/lang/String;)V");
    jstring jstr = (*env)->NewStringUTF(env,"c call Java Static Method");
    (*env)->CallStaticVoidMethod(env,cls,mid,2,jstr);

}