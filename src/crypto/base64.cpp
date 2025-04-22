//
// Created by forkernel on 2025/4/9.
//

#include "base64.h"
#include "io/fs.h"
#include "helper/convert.h"

namespace YanLib::crypto {
    std::vector<uint8_t> base64::encode(const uint8_t *data, size_t len) {
        if (len <= 0) return {};
        constexpr uint8_t BASE64_CHARS[] =
                "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::vector<uint8_t> encoded;
        encoded.reserve(4 * ((len + 2) / 3));

        size_t i = 0;
        while (i < len) {
            uint32_t triple = 0;
            int valid_bytes = 0;

            for (int j = 0; j < 3; ++j, ++i) {
                triple <<= 8;
                if (i < len) {
                    triple |= data[i];
                    valid_bytes++;
                }
            }

            int sextets = (valid_bytes * 8 + 5) / 6;
            for (int j = 0; j < 4; ++j) {
                uint8_t index = (triple >> (18 - j * 6)) & 0x3F;
                if (j < sextets) {
                    encoded.push_back(BASE64_CHARS[index]);
                } else {
                    encoded.push_back('=');
                }
            }
        }
        return encoded;
    }

    std::vector<uint8_t> base64::decode(const uint8_t *data, size_t len) {
        if (len <= 0 || len % 4 != 0) return {};

        constexpr uint8_t BASE64_CHARS[] =
                "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

        std::vector<int> decode_table(256, -1);
        for (int i = 0; i < 64; ++i) {
            decode_table[BASE64_CHARS[i]] = i;
        }
        decode_table['='] = -1;

        std::vector<uint8_t> decoded;
        decoded.reserve((len * 3) / 4);

        uint32_t buffer = 0;
        int bits_collected = 0;
        int padding = 0;

        for (size_t i = 0; i < len; ++i) {
            const uint8_t c = data[i];
            if (c == '=') {
                padding++;
                if (i < len - 2 || padding > 2) return {};
                continue;
            }
            if (decode_table[c] == -1) return {};

            buffer = (buffer << 6) | decode_table[c];
            bits_collected += 6;

            if (bits_collected >= 8) {
                decoded.push_back((buffer >> (bits_collected - 8)) & 0xFF);
                bits_collected -= 8;
            }
        }
        if (padding > 0) {
            size_t expected_size = (len - padding) * 3 / 4;
            if (decoded.size() < expected_size) return {};
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
        std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string base64::decode_string(const std::string &data) {
        std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> decoded = decode(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }

    std::string base64::encode_wstring(const std::wstring &data) {
        return encode_string(helper::convert::wstr_to_str(data));
    }

    std::string base64::decode_wstring(const std::wstring &data) {
        return decode_string(helper::convert::wstr_to_str(data));
    }

    bool base64::encode_file(const std::wstring &input_file,
                             const std::wstring &output_file) {
        io::fs input;
        io::fs output;
        HANDLE input_handle = input.open(input_file.data());
        HANDLE output_handle = output.create(output_file.data());
        if (!input_handle || !output_handle) {
            return false;
        }
        const DWORD buffer_size = input.size(input_handle);
        uint8_t *buf = new uint8_t[buffer_size];
        memset(buf, 0, buffer_size);
        DWORD bytes_read = 0;
        DWORD bytes_written = 0;
        do {
            if (!input.read(input_handle, buf, buffer_size, &bytes_read)) {
                break;
            }
            if (bytes_read <= 0) break;
            std::vector<uint8_t> encode_data = encode(buf, bytes_read);
            if (!output.write(output_handle, encode_data.data(),
                              encode_data.size(),
                              &bytes_written)) {
                break;
            }
            return true;
        } while (false);
        return false;
    }

    bool base64::decode_file(const std::wstring &input_file,
                             const std::wstring &output_file) {
        io::fs input;
        io::fs output;
        HANDLE input_handle = input.open(input_file.data());
        HANDLE output_handle = output.create(output_file.data());
        if (!input_handle || !output_handle) {
            return false;
        }
        const DWORD buffer_size = input.size(input_handle);
        uint8_t *buf = new uint8_t[buffer_size];
        memset(buf, 0, buffer_size);
        DWORD bytes_read = 0;
        DWORD bytes_written = 0;
        do {
            if (!input.read(input_handle, buf, buffer_size, &bytes_read)) {
                break;
            }
            if (bytes_read <= 0) break;
            std::vector<uint8_t> encode_data = decode(buf, bytes_read);
            if (!output.write(output_handle, encode_data.data(),
                              encode_data.size(),
                              &bytes_written)) {
                break;
            }
            return true;
        } while (false);
        return false;
    }

    std::vector<uint8_t> base64::encode_url(const uint8_t *data, size_t len) {
        if (len <= 0) return {};
        constexpr uint8_t BASE64_CHARS[] =
                "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::vector<uint8_t> encoded;
        encoded.reserve(4 * ((len + 2) / 3));

        size_t i = 0;
        while (i < len) {
            uint32_t triple = 0;
            int valid_bytes = 0;

            for (int j = 0; j < 3; ++j, ++i) {
                triple <<= 8;
                if (i < len) {
                    triple |= data[i];
                    valid_bytes++;
                }
            }

            int sextets = (valid_bytes * 8 + 5) / 6;
            for (int j = 0; j < 4; ++j) {
                uint8_t index = (triple >> (18 - j * 6)) & 0x3F;
                if (j < sextets) {
                    encoded.push_back(BASE64_CHARS[index]);
                } else {
                    encoded.push_back('=');
                }
            }
        }

        for (auto &c: encoded) {
            if (c == '+') c = '-';
            if (c == '/') c = '_';
        }
        while (!encoded.empty() && encoded.back() == '=') encoded.pop_back();

        return encoded;
    }

    std::vector<uint8_t> base64::decode_url(const uint8_t *data, size_t len) {
        if (len <= 0) return {};

        std::vector<uint8_t> modified_data(data, data + len);
        std::transform(modified_data.begin(),
                       modified_data.end(),
                       modified_data.begin(),
                       [](uint8_t c) -> uint8_t {
                           if (c == '-') return '+';
                           if (c == '_') return '/';
                           return c;
                       });

        size_t padding = (4 - (modified_data.size() % 4)) % 4;
        modified_data.insert(modified_data.end(), padding, '=');

        constexpr uint8_t BASE64_CHARS[] =
                "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::vector<int> decode_table(256, -1);
        for (int i = 0; i < 64; ++i) {
            decode_table[BASE64_CHARS[i]] = i;
        }

        std::vector<uint8_t> decoded;
        decoded.reserve((modified_data.size() * 3) / 4);

        uint32_t buffer = 0;
        int bits_collected = 0;
        bool padding_started = false;

        for (size_t i = 0; i < modified_data.size(); ++i) {
            const uint8_t c = modified_data[i];
            if (c == '=') {
                if (i < modified_data.size() - padding) return {};
                padding_started = true;
                continue;
            }

            if (decode_table[c] == -1) return {};
            if (padding_started) return {};

            buffer = (buffer << 6) | decode_table[c];
            bits_collected += 6;

            if (bits_collected >= 8) {
                decoded.push_back(
                    static_cast<uint8_t>((buffer >> (bits_collected - 8)) & 0xFF));
                bits_collected -= 8;
            }
        }

        if (padding > 0) {
            size_t expected_size = (modified_data.size() - padding) * 3 / 4;
            if (decoded.size() < expected_size) return {};
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
        std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> encoded = encode_url(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string base64::decode_url(const std::string &data) {
        std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> decoded = decode_url(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
}
