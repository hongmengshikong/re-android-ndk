#include <jni.h>
#include <string>
#include "basic.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_crypto_basic_MainActivity_BasicEncode(JNIEnv *env, jobject thiz, jstring string) {

    const char *c_str = env->GetStringUTFChars(string, nullptr);
    if (!c_str) return nullptr;

    std::string src(c_str);

    //TODO:自定义一个密钥,使用自定义密钥进行加密

    std::string key="ahh123";

    std::string result = basic_encode_with_key(src,key);


    //TODO:自定义加密
//    std::string result = basic_encode(src);

    env->ReleaseStringUTFChars(string, c_str);

    return env->NewStringUTF(result.c_str());
}