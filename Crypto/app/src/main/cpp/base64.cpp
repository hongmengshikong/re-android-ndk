#include "base64.h"

// Base64编码函数
std::string encode_base64(const std::string &src, const char* base64_table) {
    std::string encoded;
    size_t len = src.size();
    size_t i = 0;

    while (i + 3 <= len) {
        unsigned char b1 = src[i];
        unsigned char b2 = src[i + 1];
        unsigned char b3 = src[i + 2];
        encoded += base64_table[b1 >> 2];
        encoded += base64_table[((b1 & 0x03) << 4) | (b2 >> 4)];
        encoded += base64_table[((b2 & 0x0F) << 2) | (b3 >> 6)];
        encoded += base64_table[b3 & 0x3F];
        i += 3;
    }

    if (len - i == 1) {
        unsigned char b1 = src[i];
        encoded += base64_table[b1 >> 2];
        encoded += base64_table[(b1 & 0x03) << 4];
        encoded += "==";
    } else if (len - i == 2) {
        unsigned char b1 = src[i];
        unsigned char b2 = src[i + 1];
        encoded += base64_table[b1 >> 2];
        encoded += base64_table[((b1 & 0x03) << 4) | (b2 >> 4)];
        encoded += base64_table[(b2 & 0x0F) << 2];
        encoded += '=';
    }

    return encoded;
}