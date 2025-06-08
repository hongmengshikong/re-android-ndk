#include <jni.h>
#include <string>
#include "Utils.h"
#include "aes.h"


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_aescrypto_MainActivity_AESEncode(JNIEnv *env, jobject thiz, jstring string) {
    const char *c_str = env->GetStringUTFChars(string, nullptr);
    if (!c_str) return nullptr;

    std::string src(c_str);

    std::string keyStr = "this_is_aes_flag"; // 确保是16字节
    unsigned char key[16];
    StringToKey(keyStr, key);
    std::vector<unsigned char> padded = PadTo16Bytes(src);
    AES aes(key);
    for (size_t i = 0; i < padded.size(); i += 16)
        aes.Cipher(&padded[i]);

    // 将密文转成十六进制字符串
    std::string result = BytesToHex(padded);

    env->ReleaseStringUTFChars(string, c_str);

    return env->NewStringUTF(result.c_str());
}