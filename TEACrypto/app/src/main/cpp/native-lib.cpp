#include <jni.h>
#include <string>
#include "Utils.h"
#include "EncryptTEA.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_teacrypto_MainActivity_TEAEncode(JNIEnv *env, jobject thiz, jstring string) {
    const char *c_str = env->GetStringUTFChars(string, nullptr);
    if (!c_str) return nullptr;

    std::string src(c_str);
    std::string keyStr = "thisisakey123456";
    uint32_t key[4];
    StringToKey(keyStr, key);
    std::vector<uint8_t> encryptedData;
    EncryptString(src, key, encryptedData);
    std::string hexResult = BytesToHex(encryptedData);
    env->ReleaseStringUTFChars(string, c_str);
    return env->NewStringUTF(hexResult.c_str());
}