//
// Created by forkernel on 2025/4/10.
//

#include "xxencode.h"

namespace YanLib::crypto {
    std::vector<unsigned char> xxencode::encode(const std::vector<unsigned char> &data) {
        if (data.empty()) return {};
        const std::string base =
                "+-0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        std::vector<unsigned char> encoded;
        size_t total_size = data.size();
        size_t index = 0;

        while (index < total_size) {
            size_t chunk_size = std::min(total_size - index,
                                         static_cast<size_t>(45));
            encoded.push_back(base[chunk_size]);

            size_t groups = (chunk_size + 2) / 3;
            for (size_t g = 0; g < groups; ++g) {
                size_t pos = index + g * 3;
                unsigned char b1 = (pos < index + chunk_size) ? data[pos] : 0;
                unsigned char b2 = (pos + 1 < index + chunk_size) ? data[pos + 1] : 0;
                unsigned char b3 = (pos + 2 < index + chunk_size) ? data[pos + 2] : 0;

                unsigned char c1 = (b1 >> 2) & 0x3F;
                unsigned char c2 = ((b1 & 0x03) << 4) | ((b2 >> 4) & 0x0F);
                unsigned char c3 = ((b2 & 0x0F) << 2) | ((b3 >> 6) & 0x03);
                unsigned char c4 = b3 & 0x3F;

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

    std::vector<unsigned char> xxencode::decode(const std::vector<unsigned char> &data) {
        if (data.empty()) return {};
        const std::string base =
                "+-0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        std::vector<unsigned char> decoded;
        std::vector<std::vector<unsigned char> > lines;
        size_t i = 0;

        while (i < data.size()) {
            size_t start = i;
            while (i < data.size() && data[i] != '\r' && data[i] != '\n') ++i;
            lines.emplace_back(data.begin() + start, data.begin() + i);
            if (i < data.size() && data[i] == '\r') i += 2;
            else if (i < data.size()) ++i;
        }

        for (const auto &line: lines) {
            if (line.empty()) continue;

            size_t chunk_size = base.find(line[0]);
            if (chunk_size == std::string::npos) continue;

            size_t prev_size = decoded.size();
            size_t groups = (line.size() - 1) / 4;

            for (size_t g = 0; g < groups; ++g) {
                size_t pos = 1 + g * 4;
                if (pos + 3 >= line.size()) break;

                unsigned char c1 = base.find(line[pos]);
                unsigned char c2 = base.find(line[pos + 1]);
                unsigned char c3 = base.find(line[pos + 2]);
                unsigned char c4 = base.find(line[pos + 3]);

                if (c1 == std::string::npos ||
                    c2 == std::string::npos ||
                    c3 == std::string::npos ||
                    c4 == std::string::npos)
                    continue;

                unsigned char b1 = (c1 << 2) | (c2 >> 4);
                unsigned char b2 = ((c2 & 0x0F) << 4) | (c3 >> 2);
                unsigned char b3 = ((c3 & 0x03) << 6) | c4;

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
        std::vector<unsigned char> input(data.begin(), data.end());
        std::vector<unsigned char> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string xxencode::decode_string(const std::string &data) {
        std::vector<unsigned char> input(data.begin(), data.end());
        std::vector<unsigned char> decoded = decode(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
}
