#include <jni.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "RSA.h"

using namespace std;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_crypto_rsa_MainActivity_RSAEncode(JNIEnv *env, jobject thiz, jstring string) {
    const char *c_str = env->GetStringUTFChars(string, nullptr);
    if (!c_str) return nullptr;

    std::string src(c_str);

    RSA rsa;
    // 加密
    vector<long long> cipherText = rsa.Encrypt(src);
    stringstream ss;

    for (long long cipher : cipherText) {
        ss << cipher << " ";
    }
    std::string result = ss.str();

    env->ReleaseStringUTFChars(string, c_str);

    return env->NewStringUTF(result.c_str());
}