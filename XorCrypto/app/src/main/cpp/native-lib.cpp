#include <jni.h>
#include <string>
#include "xor.h"


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_xorcrypto_MainActivity_XorEncode(JNIEnv *env, jobject thiz, jstring str) {
    const char *c_str = env->GetStringUTFChars(str, nullptr);
    if (!c_str) return nullptr;

    std::string src(c_str);

    //内置密钥加密
//    std::string result = xor_encrypt(src);

    //自定义密钥加密
    std::string key = "my_secret_key";
    std::string result = xor_encrypt_with_key(src, key);


    env->ReleaseStringUTFChars(str, c_str);
    return env->NewStringUTF(result.c_str());
}