#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <cstdint>
#include <bitset>
#include "des.h"


std::string BytesToHex(const std::vector<uint8_t>& data);
void StringToKey(const std::string& strKey, uint32_t key[4]);

void StringToKey(const std::string& strKey,unsigned char key[16]);
// 将任意长度字符串用 PKCS#7 补齐到 16 的倍数
std::vector<unsigned char> PadTo16Bytes(const std::string& input);
// 从解密后的数据中移除 PKCS#7 补齐
void RemovePadding(std::vector<unsigned char>& data);

// 将8字节字符串转换为64位Block
Block stringToBlock(const std::string& str);

// 将64位Block转换为字符串
std::string blockToString(const Block& block);

// 将任意长度字符串转换为多个Block
std::vector<Block> stringToBlocks(const std::string& input);

// 将多个Block组合为字符串
std::string blocksToString(const std::vector<Block>& blocks);

std::string blockToHex(const std::vector<Block>& blocks);

std::vector<uint8_t> blockToBytes(const Block& block);

#endif // UTILS_H
