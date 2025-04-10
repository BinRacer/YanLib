//
// Created by forkernel on 2025/4/10.
//

#include "uuencode.h"

namespace YanLib::crypto {
    std::vector<unsigned char> uuencode::encode(const std::vector<unsigned char> &data) {
        if (data.empty()) return {};
        std::vector<unsigned char> output;
        size_t buff_len = data.size();
        size_t bytes_processed = 0;

        while (bytes_processed < buff_len) {
            size_t bytes_left = buff_len - bytes_processed;
            size_t n_actual = std::min(bytes_left, static_cast<size_t>(45));
            size_t padded_len = ((n_actual + 2) / 3) * 3;

            output.push_back(static_cast<unsigned char>(n_actual + 32));

            for (int i = 0; i < padded_len; i += 3) {
                unsigned char trio[3] = {};
                for (int j = 0; j < 3; ++j) {
                    size_t pos = bytes_processed + i + j;
                    trio[j] = (pos < buff_len) ? data[pos] : 0;
                }

                unsigned char c1 = (trio[0] >> 2) & 0x3F;
                unsigned char c2 = ((trio[0] << 4) & 0x30) | ((trio[1] >> 4) & 0x0F);
                unsigned char c3 = ((trio[1] << 2) & 0x3C) | ((trio[2] >> 6) & 0x03);
                unsigned char c4 = trio[2] & 0x3F;

                auto encode_char = [](const unsigned char c) {
                    return (c == 0) ? 96 : c + 32;
                };
                output.push_back(encode_char(c1));
                output.push_back(encode_char(c2));
                output.push_back(encode_char(c3));
                output.push_back(encode_char(c4));
            }

            output.push_back('\n');
            bytes_processed += n_actual;
        }

        output.push_back(96);
        output.push_back('\n');
        return output;
    }

    std::vector<unsigned char> uuencode::decode(const std::vector<unsigned char> &data) {
        if (data.empty()) return {};
        std::vector<unsigned char> output;
        size_t in_index = 0;
        size_t total_len = 0;

        while (in_index < data.size()) {
            size_t line_end = in_index;
            while (line_end < data.size() && data[line_end] != '\n') {
                ++line_end;
            }

            if (line_end == in_index) {
                ++in_index;
                continue;
            }

            unsigned char n_char = data[in_index];
            int n_actual = (n_char - 32) & 0x3F;

            if (n_actual == 0) break;
            if (n_actual > 45) return {};

            int expected_chars = ((n_actual + 2) / 3) * 4;
            size_t data_start = in_index + 1;
            size_t data_end = data_start + expected_chars;

            if (data_end > line_end) return {};

            size_t output_before = output.size();
            for (int i = 0; i < expected_chars; i += 4) {
                if (data_start + i + 3 >= data.size()) return {};

                unsigned char c1 = data[data_start + i];
                unsigned char c2 = data[data_start + i + 1];
                unsigned char c3 = data[data_start + i + 2];
                unsigned char c4 = data[data_start + i + 3];

                auto is_valid = [](unsigned char c) {
                    return c >= 32 && c <= 95;
                };
                if (!is_valid(c1) ||
                    !is_valid(c2) ||
                    !is_valid(c3) ||
                    !is_valid(c4))
                    return {};

                unsigned char v1 = (c1 - 32) & 0x3F;
                unsigned char v2 = (c2 - 32) & 0x3F;
                unsigned char v3 = (c3 - 32) & 0x3F;
                unsigned char v4 = (c4 - 32) & 0x3F;

                output.push_back((v1 << 2) | (v2 >> 4));
                output.push_back(((v2 & 0x0F) << 4) | (v3 >> 2));
                output.push_back(((v3 & 0x03) << 6) | v4);
            }

            output.resize(output_before + n_actual);
            total_len += n_actual;
            in_index = line_end + 1;
        }

        return output;
    }

    std::string uuencode::encode_string(const std::string &data) {
        std::vector<unsigned char> input(data.begin(), data.end());
        std::vector<unsigned char> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string uuencode::decode_string(const std::string &data) {
        std::vector<unsigned char> input(data.begin(), data.end());
        std::vector<unsigned char> decoded = decode(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
}
