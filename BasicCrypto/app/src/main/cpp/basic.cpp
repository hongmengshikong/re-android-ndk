#include "basic.h"
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdint>

std::string basic_encode_with_key(const std::string& plaintext, const std::string& key_str){
    //TODO:实现加密方法

    //TODO:返回密文
    //这里为了编译通过，返回的是传过来的明文数据，未对数据进行加密处理
    return plaintext+key_str;
}
std::string basic_encode(const std::string& plaintext){
    //TODO:实现加密方法

    //TODO:返回密文
    //这里为了编译通过，返回的是传过来的明文数据，未对数据进行加密处理
    return plaintext;
}