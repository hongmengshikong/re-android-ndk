#include <jni.h>
#include <string>
#include "Utils.h"



extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_descrypto_MainActivity_DESEncode(JNIEnv *env, jobject thiz, jstring string) {
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