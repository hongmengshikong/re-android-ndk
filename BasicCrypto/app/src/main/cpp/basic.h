//
// Created by 时空 on 2025/6/9.
//

#ifndef BASIC_H
#define BASIC_H

#include <string>
std::string basic_encode(const std::string& plaintext);

// 可选：带自定义密钥的加密版本
std::string basic_encode_with_key(const std::string& plaintext, const std::string& key_str);


#endif //BASIC_H
