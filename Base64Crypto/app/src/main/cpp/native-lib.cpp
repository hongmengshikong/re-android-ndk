#include <jni.h>
#include <string>
#include "base64.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_crypto_base64_MainActivity_Base64Encode(JNIEnv *env, jobject thiz, jstring str) {
    const char *c_str = env->GetStringUTFChars(str, nullptr);
    if (!c_str) return nullptr;

    std::string src(c_str);
    std::string result = base64_encode(src);
    env->ReleaseStringUTFChars(str, c_str);

    return env->NewStringUTF(result.c_str());
}