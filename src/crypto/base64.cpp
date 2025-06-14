/* clang-format off */
/*
 * @file base64.cpp
 * @date 2025-04-09
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
#include "base64.h"
#include "helper/convert.h"
#include <algorithm>

namespace YanLib::crypto {
    std::vector<uint8_t> base64::encode(const uint8_t *data, const size_t len) {
        if (len <= 0)
            return {};
        constexpr uint8_t BASE64_CHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghi"
                                           "jklmnopqrstuvwxyz0123456789+/";
        std::vector<uint8_t> encoded;
        encoded.reserve(4 * ((len + 2) / 3));

        size_t i = 0;
        while (i < len) {
            uint32_t triple = 0;
            int32_t valid_bytes = 0;

            for (int32_t j = 0; j < 3; ++j, ++i) {
                triple <<= 8;
                if (i < len) {
                    triple |= data[i];
                    valid_bytes++;
                }
            }

            const int32_t sextets = (valid_bytes * 8 + 5) / 6;
            for (int32_t j = 0; j < 4; ++j) {
                const uint8_t index = (triple >> (18 - j * 6)) & 0x3F;
                if (j < sextets) {
                    encoded.push_back(BASE64_CHARS[index]);
                } else {
                    encoded.push_back('=');
                }
            }
        }
        return encoded;
    }

    std::vector<uint8_t> base64::decode(const uint8_t *data, const size_t len) {
        if (len <= 0 || len % 4 != 0)
            return {};

        constexpr uint8_t BASE64_CHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghi"
                                           "jklmnopqrstuvwxyz0123456789+/";

        std::vector decode_table(256, -1);
        for (int32_t i = 0; i < 64; ++i) {
            decode_table[BASE64_CHARS[i]] = i;
        }
        decode_table['='] = -1;

        std::vector<uint8_t> decoded;
        decoded.reserve((len * 3) / 4);

        uint32_t buffer = 0;
        int32_t bits_collected = 0;
        int32_t padding = 0;

        for (size_t i = 0; i < len; ++i) {
            const uint8_t c = data[i];
            if (c == '=') {
                padding++;
                if (i < len - 2 || padding > 2)
                    return {};
                continue;
            }
            if (decode_table[c] == -1)
                return {};

            buffer = (buffer << 6) | decode_table[c];
            bits_collected += 6;

            if (bits_collected >= 8) {
                decoded.push_back((buffer >> (bits_collected - 8)) & 0xFF);
                bits_collected -= 8;
            }
        }
        if (padding > 0) {
            const size_t expected_size = (len - padding) * 3 / 4;
            if (decoded.size() < expected_size)
                return {};
            decoded.resize(expected_size);
        }
        return decoded;
    }

    std::vector<uint8_t> base64::encode(const std::vector<uint8_t> &data) {
        return encode(data.data(), data.size());
    }

    std::vector<uint8_t> base64::decode(const std::vector<uint8_t> &data) {
        return decode(data.data(), data.size());
    }

    std::string base64::encode_string(const std::string &data) {
        const std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string base64::decode_string(const std::string &data) {
        const std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> decoded = decode(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }

    bool base64::encode_file(const std::string &input_file,
                             const std::string &output_file) {
        HANDLE input =
                CreateFileA(input_file.data(), GENERIC_READ | GENERIC_WRITE,
                            FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (input == INVALID_HANDLE_VALUE) {
            return false;
        }
        HANDLE output =
                CreateFileA(output_file.data(), GENERIC_READ | GENERIC_WRITE,
                            FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (output == INVALID_HANDLE_VALUE) {
            return false;
        }
        bool result = false;
        do {
            LARGE_INTEGER file_size{};
            if (!GetFileSizeEx(input, &file_size)) {
                break;
            }
            const uint32_t buffer_size = file_size.QuadPart;
            std::vector<uint8_t> buf(buffer_size, '\0');
            unsigned long bytes_read = 0;
            unsigned long bytes_written = 0;
            if (!ReadFile(input, buf.data(), buffer_size, &bytes_read,
                          nullptr)) {
                break;
            }
            if (bytes_read <= 0)
                break;
            const std::vector<uint8_t> encode_data =
                    encode(buf.data(), bytes_read);
            if (!WriteFile(output, encode_data.data(), encode_data.size(),
                           &bytes_written, nullptr)) {
                break;
            }
            result = true;
        } while (false);
        if (input != INVALID_HANDLE_VALUE) {
            CloseHandle(input);
        }
        if (output != INVALID_HANDLE_VALUE) {
            CloseHandle(output);
        }
        return result;
    }

    bool base64::encode_file(const std::wstring &input_file,
                             const std::wstring &output_file) {
        HANDLE input =
                CreateFileW(input_file.data(), GENERIC_READ | GENERIC_WRITE,
                            FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (input == INVALID_HANDLE_VALUE) {
            return false;
        }
        HANDLE output =
                CreateFileW(output_file.data(), GENERIC_READ | GENERIC_WRITE,
                            FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (output == INVALID_HANDLE_VALUE) {
            return false;
        }
        bool result = false;
        do {
            LARGE_INTEGER file_size{};
            if (!GetFileSizeEx(input, &file_size)) {
                break;
            }
            const uint32_t buffer_size = file_size.QuadPart;
            std::vector<uint8_t> buf(buffer_size, '\0');
            unsigned long bytes_read = 0;
            unsigned long bytes_written = 0;
            if (!ReadFile(input, buf.data(), buffer_size, &bytes_read,
                          nullptr)) {
                break;
            }
            if (bytes_read <= 0)
                break;
            const std::vector<uint8_t> encode_data =
                    encode(buf.data(), bytes_read);
            if (!WriteFile(output, encode_data.data(), encode_data.size(),
                           &bytes_written, nullptr)) {
                break;
            }
            result = true;
        } while (false);
        if (input != INVALID_HANDLE_VALUE) {
            CloseHandle(input);
        }
        if (output != INVALID_HANDLE_VALUE) {
            CloseHandle(output);
        }
        return result;
    }

    bool base64::decode_file(const std::string &input_file,
                             const std::string &output_file) {
        HANDLE input =
                CreateFileA(input_file.data(), GENERIC_READ | GENERIC_WRITE,
                            FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (input == INVALID_HANDLE_VALUE) {
            return false;
        }
        HANDLE output =
                CreateFileA(output_file.data(), GENERIC_READ | GENERIC_WRITE,
                            FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (output == INVALID_HANDLE_VALUE) {
            return false;
        }
        bool result = false;
        do {
            LARGE_INTEGER file_size{};
            if (!GetFileSizeEx(input, &file_size)) {
                break;
            }
            const uint32_t buffer_size = file_size.QuadPart;
            std::vector<uint8_t> buf(buffer_size, '\0');
            unsigned long bytes_read = 0;
            unsigned long bytes_written = 0;
            if (!ReadFile(input, buf.data(), buffer_size, &bytes_read,
                          nullptr)) {
                break;
            }
            if (bytes_read <= 0)
                break;
            const std::vector<uint8_t> decode_data =
                    decode(buf.data(), bytes_read);
            if (!WriteFile(output, decode_data.data(), decode_data.size(),
                           &bytes_written, nullptr)) {
                break;
            }
            result = true;
        } while (false);
        if (input != INVALID_HANDLE_VALUE) {
            CloseHandle(input);
        }
        if (output != INVALID_HANDLE_VALUE) {
            CloseHandle(output);
        }
        return result;
    }

    bool base64::decode_file(const std::wstring &input_file,
                             const std::wstring &output_file) {
        HANDLE input =
                CreateFileW(input_file.data(), GENERIC_READ | GENERIC_WRITE,
                            FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (input == INVALID_HANDLE_VALUE) {
            return false;
        }
        HANDLE output =
                CreateFileW(output_file.data(), GENERIC_READ | GENERIC_WRITE,
                            FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (output == INVALID_HANDLE_VALUE) {
            return false;
        }
        bool result = false;
        do {
            LARGE_INTEGER file_size{};
            if (!GetFileSizeEx(input, &file_size)) {
                break;
            }
            const uint32_t buffer_size = file_size.QuadPart;
            std::vector<uint8_t> buf(buffer_size, '\0');
            unsigned long bytes_read = 0;
            unsigned long bytes_written = 0;
            if (!ReadFile(input, buf.data(), buffer_size, &bytes_read,
                          nullptr)) {
                break;
            }
            if (bytes_read <= 0)
                break;
            const std::vector<uint8_t> decode_data =
                    decode(buf.data(), bytes_read);
            if (!WriteFile(output, decode_data.data(), decode_data.size(),
                           &bytes_written, nullptr)) {
                break;
            }
            result = true;
        } while (false);
        if (input != INVALID_HANDLE_VALUE) {
            CloseHandle(input);
        }
        if (output != INVALID_HANDLE_VALUE) {
            CloseHandle(output);
        }
        return result;
    }

    std::vector<uint8_t> base64::encode_url(const uint8_t *data,
                                            const size_t len) {
        if (len <= 0)
            return {};
        constexpr uint8_t BASE64_CHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghi"
                                           "jklmnopqrstuvwxyz0123456789+/";
        std::vector<uint8_t> encoded;
        encoded.reserve(4 * ((len + 2) / 3));

        size_t i = 0;
        while (i < len) {
            uint32_t triple = 0;
            int32_t valid_bytes = 0;

            for (int32_t j = 0; j < 3; ++j, ++i) {
                triple <<= 8;
                if (i < len) {
                    triple |= data[i];
                    valid_bytes++;
                }
            }

            const int32_t sextets = (valid_bytes * 8 + 5) / 6;
            for (int32_t j = 0; j < 4; ++j) {
                const uint8_t index = (triple >> (18 - j * 6)) & 0x3F;
                if (j < sextets) {
                    encoded.push_back(BASE64_CHARS[index]);
                } else {
                    encoded.push_back('=');
                }
            }
        }

        for (auto &c : encoded) {
            if (c == '+')
                c = '-';
            if (c == '/')
                c = '_';
        }
        while (!encoded.empty() && encoded.back() == '=')
            encoded.pop_back();

        return encoded;
    }

    std::vector<uint8_t> base64::decode_url(const uint8_t *data,
                                            const size_t len) {
        if (len <= 0)
            return {};

        std::vector modified_data(data, data + len);
        std::transform(modified_data.begin(), modified_data.end(),
                       modified_data.begin(), [](const uint8_t c) -> uint8_t {
                           if (c == '-')
                               return '+';
                           if (c == '_')
                               return '/';
                           return c;
                       });

        const size_t padding = (4 - (modified_data.size() % 4)) % 4;
        modified_data.insert(modified_data.end(), padding, '=');

        constexpr uint8_t BASE64_CHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghi"
                                           "jklmnopqrstuvwxyz0123456789+/";
        std::vector decode_table(256, -1);
        for (int32_t i = 0; i < 64; ++i) {
            decode_table[BASE64_CHARS[i]] = i;
        }

        std::vector<uint8_t> decoded;
        decoded.reserve((modified_data.size() * 3) / 4);

        uint32_t buffer = 0;
        int32_t bits_collected = 0;
        bool padding_started = false;

        for (size_t i = 0; i < modified_data.size(); ++i) {
            const uint8_t c = modified_data[i];
            if (c == '=') {
                if (i < modified_data.size() - padding)
                    return {};
                padding_started = true;
                continue;
            }

            if (decode_table[c] == -1)
                return {};
            if (padding_started)
                return {};

            buffer = (buffer << 6) | decode_table[c];
            bits_collected += 6;

            if (bits_collected >= 8) {
                decoded.push_back(static_cast<uint8_t>(
                        (buffer >> (bits_collected - 8)) & 0xFF));
                bits_collected -= 8;
            }
        }

        if (padding > 0) {
            const size_t expected_size =
                    (modified_data.size() - padding) * 3 / 4;
            if (decoded.size() < expected_size)
                return {};
            decoded.resize(expected_size);
        }

        return decoded;
    }

    std::vector<uint8_t> base64::encode_url(const std::vector<uint8_t> &data) {
        return encode_url(data.data(), data.size());
    }

    std::vector<uint8_t> base64::decode_url(const std::vector<uint8_t> &data) {
        return decode_url(data.data(), data.size());
    }

    std::string base64::encode_url(const std::string &data) {
        const std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> encoded = encode_url(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string base64::decode_url(const std::string &data) {
        const std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> decoded = decode_url(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
} // namespace YanLib::crypto
