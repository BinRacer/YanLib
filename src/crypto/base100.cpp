//
// Created by forkernel on 2025/4/10.
//

#include "base100.h"

namespace YanLib::crypto {
    std::vector<uint8_t> base100::encode(const std::vector<uint8_t> &data) {
        if (data.empty()) return {};
        std::vector<uint8_t> result;
        result.reserve(data.size() * 4);

        for (const auto ch: data) {
            uint32_t temp = static_cast<uint32_t>(ch) + 55;
            uint8_t byte3 = (temp >> 6) + 143;
            uint8_t byte4 = (temp & 0x3F) + 128;

            result.push_back(0xF0);
            result.push_back(0x9F);
            result.push_back(byte3);
            result.push_back(byte4);
        }
        return result;
    }

    std::vector<uint8_t> base100::decode(const std::vector<uint8_t> &data) {
        std::vector<uint8_t> result;

        if (data.empty() || data.size() % 4 != 0) return {};
        result.reserve(data.size() / 4);

        for (size_t i = 0; i < data.size(); i += 4) {
            if (data[i] != 0xF0 || data[i + 1] != 0x9F) return {};

            uint8_t byte3 = data[i + 2];
            uint8_t byte4 = data[i + 3];

            int32_t decoded = ((byte3 - 143) << 6) | (byte4 - 128);
            decoded -= 55;

            if (decoded < 0 || decoded > 255) return {};

            result.push_back(static_cast<uint8_t>(decoded));
        }
        return result;
    }

    std::string base100::encode_string(const std::string &data) {
        std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string base100::decode_string(const std::string &data) {
        std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> decoded = decode(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
}
