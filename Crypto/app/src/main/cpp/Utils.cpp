#include "Utils.h"
#include <cstring>

std::string BytesToHex(const std::vector<uint8_t>& data) {
    const char* hex_chars = "0123456789ABCDEF";
    std::string hex;
    hex.reserve(data.size() * 2);

    for (uint8_t byte : data) {
        hex += hex_chars[(byte >> 4) & 0xF];
        hex += hex_chars[byte & 0xF];
    }

    return hex;
}

void StringToKey(const std::string& strKey, uint32_t key[4]) {
    std::string paddedKey = strKey;
    paddedKey.resize(16, '\0');  // Ensure it is at least 16 bytes
    std::memcpy(key, paddedKey.data(), 16); // Copy 16 bytes into 4 uint32_t
}

void StringToKey(const std::string& strKey, unsigned char key[16]) {
    std::string paddedKey = strKey;
    paddedKey.resize(16, '\0');  // pad to 16 bytes
    std::memcpy(key, paddedKey.data(), 16);
}
std::vector<unsigned char> PadTo16Bytes(const std::string& input) {
    std::vector<unsigned char> padded(input.begin(), input.end());
    size_t padLen = 16 - (padded.size() % 16);
    padded.insert(padded.end(), padLen, static_cast<unsigned char>(padLen));
    return padded;
}

void RemovePadding(std::vector<unsigned char>& data) {
    if (data.empty()) return;
    unsigned char padLen = data.back();
    if (padLen > 16) return; // 防止异常 padding
    data.resize(data.size() - padLen);
}

Block stringToBlock(const std::string& str) {
    Block block;
    for (int i = 0; i < 8 && i < str.size(); ++i) {
        for (int j = 0; j < 8; ++j) {
            block[63 - (i * 8 + j)] = (str[i] >> (7 - j)) & 1;
        }
    }
    return block;
}

std::string blockToString(const Block& block) {
    std::string str(8, '\0');
    for (int i = 0; i < 8; ++i) {
        unsigned char ch = 0;
        for (int j = 0; j < 8; ++j) {
            ch |= block[63 - (i * 8 + j)] << (7 - j);
        }
        str[i] = ch;
    }
    return str;
}

std::vector<Block> stringToBlocks(const std::string& input) {
    std::vector<Block> blocks;
    for (size_t i = 0; i < input.size(); i += 8) {
        std::string chunk = input.substr(i, 8);
        while (chunk.size() < 8) chunk.push_back('\0');  // 补0
        blocks.push_back(stringToBlock(chunk));
    }
    return blocks;
}

std::string blocksToString(const std::vector<Block>& blocks) {
    std::string output;
    for (const auto& blk : blocks) {
        output += blockToString(blk);
    }
    return output;
}

std::string blockToHex(const std::vector<Block>& blocks) {
    std::string result;
    for (const auto& blk : blocks) {
        std::vector<uint8_t> bytes = blockToBytes(blk); // 每个 Block 转为 8 字节
        result += BytesToHex(bytes); // 转为 hex 字符串并拼接
    }
    return result;
}




std::vector<uint8_t> blockToBytes(const Block& block) {
    std::vector<uint8_t> bytes(8);
    for (int i = 0; i < 8; ++i) {
        uint8_t byte = 0;
        for (int j = 0; j < 8; ++j) {
            byte |= block[63 - (i * 8 + j)] << (7 - j);
        }
        bytes[i] = byte;
    }
    return bytes;
}
