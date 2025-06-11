#include <jni.h>
#include <string>
#include "md5.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_crypto_md5_MainActivity_MD5Encode(JNIEnv *env, jobject thiz, jstring string) {
    const char *c_str = env->GetStringUTFChars(string, nullptr);
    if (!c_str) return nullptr;

    std::string src(c_str);

    std::string result = MD5(src).toStr();

    env->ReleaseStringUTFChars(string, c_str);

    return env->NewStringUTF(result.c_str());
}