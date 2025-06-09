#include <jni.h>
#include <string>
#include "base64.h"
#include "xor.h"
#include "Utils.h"
#include "EncryptTEA.h"
#include "aes.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_crypto_MainActivity_Base64Encode(JNIEnv *env, jobject thiz, jstring str) {
    const char *c_str = env->GetStringUTFChars(str, nullptr);
    if (!c_str) return nullptr;

    std::string src(c_str);
    std::string result = base64_encode(src);
    env->ReleaseStringUTFChars(str, c_str);

    return env->NewStringUTF(result.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_crypto_MainActivity_XorEncode(JNIEnv *env, jobject thiz, jstring str) {
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
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_crypto_MainActivity_TEAEncode(JNIEnv *env, jobject thiz, jstring string) {
    const char *c_str = env->GetStringUTFChars(string, nullptr);
    if (!c_str) return nullptr;

    std::string src(c_str);
    std::string keyStr = "this_is_tea_flag";
    uint32_t key[4];
    StringToKey(keyStr, key);
    std::vector<uint8_t> encryptedData;
    EncryptString(src, key, encryptedData);
    std::string hexResult = BytesToHex(encryptedData);
    env->ReleaseStringUTFChars(string, c_str);
    return env->NewStringUTF(hexResult.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_crypto_MainActivity_AESEncode(JNIEnv *env, jobject thiz, jstring string) {
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
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_crypto_MainActivity_DESEncode(JNIEnv *env, jobject thiz, jstring string) {
    const char *c_str = env->GetStringUTFChars(string, nullptr);
    if (!c_str) return nullptr;

    std::string src(c_str);

    std::string keyText = "MySecrK1";

    Block key = stringToBlock(keyText);

    std::vector<Block> blocks = stringToBlocks(src);
    std::vector<Block> encryptedBlocks;

    // 加密每个分组
    for (auto blk : blocks) {
        des(blk, key, e);
        encryptedBlocks.push_back(blk);
    }

    std::string result = blockToHex(encryptedBlocks);

//    std::string result = encode_base64(src,base64_table);

    env->ReleaseStringUTFChars(string, c_str);

    return env->NewStringUTF(result.c_str());
}