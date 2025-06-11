/* clang-format off */
/*
 * @file uuencode.cpp
 * @date 2025-04-10
 * @license MIT License
 *
 * Copyright (c) 2025 BinRacer <native.lab@outlook.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* clang-format on */
#include "uuencode.h"

namespace YanLib::crypto {
    std::vector<uint8_t> uuencode::encode(const std::vector<uint8_t> &data) {
        if (data.empty())
            return {};
        std::vector<uint8_t> output;
        const size_t buff_len = data.size();
        size_t bytes_processed = 0;

        while (bytes_processed < buff_len) {
            size_t bytes_left = buff_len - bytes_processed;
            const size_t n_actual =
                    std::min(bytes_left, static_cast<size_t>(45));
            const size_t padded_len = ((n_actual + 2) / 3) * 3;

            output.push_back(static_cast<uint8_t>(n_actual + 32));

            for (int32_t i = 0; i < padded_len; i += 3) {
                uint8_t trio[3] = {};
                for (int32_t j = 0; j < 3; ++j) {
                    const size_t pos = bytes_processed + i + j;
                    trio[j] = (pos < buff_len) ? data[pos] : 0;
                }

                const uint8_t c1 = (trio[0] >> 2) & 0x3F;
                const uint8_t c2 =
                        ((trio[0] << 4) & 0x30) | ((trio[1] >> 4) & 0x0F);
                const uint8_t c3 =
                        ((trio[1] << 2) & 0x3C) | ((trio[2] >> 6) & 0x03);
                const uint8_t c4 = trio[2] & 0x3F;

                auto encode_char = [](const uint8_t c) {
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

    std::vector<uint8_t> uuencode::decode(const std::vector<uint8_t> &data) {
        if (data.empty())
            return {};
        std::vector<uint8_t> output;
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

            const uint8_t n_char = data[in_index];
            const int32_t n_actual = (n_char - 32) & 0x3F;

            if (n_actual == 0)
                break;
            if (n_actual > 45)
                return {};

            const int32_t expected_chars = ((n_actual + 2) / 3) * 4;
            const size_t data_start = in_index + 1;
            if (const size_t data_end = data_start + expected_chars;
                data_end > line_end)
                return {};

            const size_t output_before = output.size();
            for (int32_t i = 0; i < expected_chars; i += 4) {
                if (data_start + i + 3 >= data.size())
                    return {};

                const uint8_t c1 = data[data_start + i];
                const uint8_t c2 = data[data_start + i + 1];
                const uint8_t c3 = data[data_start + i + 2];
                const uint8_t c4 = data[data_start + i + 3];

                auto is_valid = [](const uint8_t c) {
                    return c >= 32 && c <= 95;
                };
                if (!is_valid(c1) || !is_valid(c2) || !is_valid(c3) ||
                    !is_valid(c4))
                    return {};

                const uint8_t v1 = (c1 - 32) & 0x3F;
                const uint8_t v2 = (c2 - 32) & 0x3F;
                const uint8_t v3 = (c3 - 32) & 0x3F;
                const uint8_t v4 = (c4 - 32) & 0x3F;

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
        const std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string uuencode::decode_string(const std::string &data) {
        const std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> decoded = decode(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
} // namespace YanLib::crypto
