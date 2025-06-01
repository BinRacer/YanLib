//
// Created by forkernel on 2025/4/10.
//

#include "xxencode.h"

namespace YanLib::crypto {
    std::vector<uint8_t> xxencode::encode(const std::vector<uint8_t> &data) {
        if (data.empty())
            return {};
        const std::string base = "+-"
                                 "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghi"
                                 "jklmnopqrstuvwxyz";
        std::vector<uint8_t> encoded;
        size_t total_size = data.size();
        size_t index = 0;

        while (index < total_size) {
            size_t chunk_size =
                    std::min(total_size - index, static_cast<size_t>(45));
            encoded.push_back(base[chunk_size]);

            size_t groups = (chunk_size + 2) / 3;
            for (size_t g = 0; g < groups; ++g) {
                size_t pos = index + g * 3;
                uint8_t b1 = (pos < index + chunk_size) ? data[pos] : 0;
                uint8_t b2 = (pos + 1 < index + chunk_size) ? data[pos + 1] : 0;
                uint8_t b3 = (pos + 2 < index + chunk_size) ? data[pos + 2] : 0;

                uint8_t c1 = (b1 >> 2) & 0x3F;
                uint8_t c2 = ((b1 & 0x03) << 4) | ((b2 >> 4) & 0x0F);
                uint8_t c3 = ((b2 & 0x0F) << 2) | ((b3 >> 6) & 0x03);
                uint8_t c4 = b3 & 0x3F;

                encoded.push_back(base[c1]);
                encoded.push_back(base[c2]);
                encoded.push_back(base[c3]);
                encoded.push_back(base[c4]);
            }

            if (index + chunk_size < total_size) {
                encoded.push_back('\r');
                encoded.push_back('\n');
            }
            index += chunk_size;
        }
        return encoded;
    }

    std::vector<uint8_t> xxencode::decode(const std::vector<uint8_t> &data) {
        if (data.empty())
            return {};
        const std::string base = "+-"
                                 "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghi"
                                 "jklmnopqrstuvwxyz";
        std::vector<uint8_t> decoded;
        std::vector<std::vector<uint8_t>> lines;
        int64_t i = 0;

        while (i < data.size()) {
            int64_t start = i;
            while (i < data.size() && data[i] != '\r' && data[i] != '\n')
                ++i;
            lines.emplace_back(data.begin() + start, data.begin() + i);
            if (i < data.size() && data[i] == '\r')
                i += 2;
            else if (i < data.size())
                ++i;
        }

        for (const auto &line : lines) {
            if (line.empty())
                continue;

            size_t chunk_size = base.find(static_cast<char>(line[0]));
            if (chunk_size == std::string::npos)
                continue;

            size_t prev_size = decoded.size();
            size_t groups = (line.size() - 1) / 4;

            for (size_t g = 0; g < groups; ++g) {
                size_t pos = 1 + g * 4;
                if (pos + 3 >= line.size())
                    break;

                uint8_t c1 = base.find(static_cast<char>(line[pos]));
                uint8_t c2 = base.find(static_cast<char>(line[pos + 1]));
                uint8_t c3 = base.find(static_cast<char>(line[pos + 2]));
                uint8_t c4 = base.find(static_cast<char>(line[pos + 3]));

                if (c1 == std::string::npos || c2 == std::string::npos ||
                    c3 == std::string::npos || c4 == std::string::npos)
                    continue;

                uint8_t b1 = (c1 << 2) | (c2 >> 4);
                uint8_t b2 = ((c2 & 0x0F) << 4) | (c3 >> 2);
                uint8_t b3 = ((c3 & 0x03) << 6) | c4;

                decoded.push_back(b1);
                decoded.push_back(b2);
                decoded.push_back(b3);
            }

            if (decoded.size() > prev_size + chunk_size) {
                decoded.resize(prev_size + chunk_size);
            }
        }
        return decoded;
    }

    std::string xxencode::encode_string(const std::string &data) {
        std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string xxencode::decode_string(const std::string &data) {
        std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> decoded = decode(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
} // namespace YanLib::crypto
