// base64.h
#ifndef BASE64_H
#define BASE64_H

#include <string>

// 自定义 Base64 编码函数
std::string base64_encode(const std::string &src);

std::string base64_decode(const std::string &src);
#endif // BASE64_H