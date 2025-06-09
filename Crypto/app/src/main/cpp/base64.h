// base64.h
#ifndef BASE64_H
#define BASE64_H

#include <string>

// 自定义 Base64 编码函数
std::string encode_base64(const std::string& src, const char* base64_table);
#endif // BASE64_H