//
// Created by forkernel on 2025/4/9.
//

#include "base64.h"
#include "../io/fs.h"
#include "../helper/convert.h"

namespace YanLib::crypto {
    std::vector<unsigned char> base64::encode(const unsigned char *data, size_t len) {
        if (len <= 0) return {};
        constexpr unsigned char BASE64_CHARS[] =
                "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::vector<unsigned char> encoded;
        encoded.reserve(4 * ((len + 2) / 3));

        for (size_t i = 0; i < len;) {
            uint32_t triple = 0;
            int bits = 0;

            for (int n = 0; n < 3; ++n, ++i) {
                if (i < len) {
                    triple = (triple << 8) | data[i];
                    bits += 8;
                }
            }

            int sextets = (bits + 5) / 6;
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

    std::vector<unsigned char> base64::decode(const unsigned char *data, size_t len) {
        if (len <= 0) return {};
        constexpr unsigned char BASE64_CHARS[] =
                "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::vector<int> decode_table(256, -1);
        for (int i = 0; i < 64; ++i) {
            decode_table[BASE64_CHARS[i]] = i;
        }
        decode_table['='] = 0;

        std::vector<unsigned char> decoded;
        decoded.reserve((len * 3) / 4);

        uint32_t buffer = 0;
        int bits_collected = 0;

        for (size_t i = 0; i < len; ++i) {
            const unsigned char c = data[i];
            if (decode_table[c] < 0) continue;

            buffer = (buffer << 6) | decode_table[c];
            bits_collected += 6;

            if (bits_collected >= 8) {
                decoded.push_back((buffer >> (bits_collected - 8)) & 0xFF);
                bits_collected -= 8;
            }
        }
        return decoded;
    }

    std::vector<unsigned char> base64::encode(const std::vector<unsigned char> &data) {
        return encode(data.data(), data.size());
    }

    std::vector<unsigned char> base64::decode(const std::vector<unsigned char> &data) {
        return decode(data.data(), data.size());
    }

    std::string base64::encode_string(const std::string &data) {
        std::vector<unsigned char> input(data.begin(), data.end());
        std::vector<unsigned char> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string base64::decode_string(const std::string &data) {
        std::vector<unsigned char> input(data.begin(), data.end());
        std::vector<unsigned char> decoded = decode(input);
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
        if (!input.open(input_file.data()) ||
            !output.create(output_file.data())) {
            return false;
        }
        const DWORD bufferSize = input.size();
        unsigned char *buf = new unsigned char[bufferSize];
        memset(buf, 0, bufferSize);
        DWORD bytesRead = 0;
        DWORD bytesWrite = 0;
        do {
            if (!input.read(buf, bufferSize, &bytesRead)) {
                break;
            }
            if (bytesRead <= 0) break;
            std::vector<unsigned char> encode_data = encode(buf, bytesRead);
            if (!output.write(encode_data.data(),
                              encode_data.size(),
                              &bytesWrite)) {
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
        if (!input.open(input_file.data()) ||
            !output.create(output_file.data())) {
            return false;
        }
        const DWORD bufferSize = input.size();
        unsigned char *buf = new unsigned char[bufferSize];
        memset(buf, 0, bufferSize);
        DWORD bytesRead = 0;
        DWORD bytesWrite = 0;
        do {
            if (!input.read(buf, bufferSize, &bytesRead)) {
                break;
            }
            if (bytesRead <= 0) break;
            std::vector<unsigned char> encode_data = decode(buf, bytesRead);
            if (!output.write(encode_data.data(),
                              encode_data.size(),
                              &bytesWrite)) {
                break;
            }
            return true;
        } while (false);
        return false;
    }

    std::string base64::encode_url(const std::string &data) {
        if (data.empty()) return {};
        // replace '+','/' to '-','_'
        constexpr char BASE64_CHARS[] =
                "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
        std::string encoded;
        size_t len = data.size();
        encoded.reserve(4 * ((len + 2) / 3));

        for (size_t i = 0; i < len;) {
            uint32_t triple = 0;
            int bits = 0;

            for (int n = 0; n < 3; ++n, ++i) {
                if (i < len) {
                    triple = (triple << 8) | data[i];
                    bits += 8;
                }
            }

            int sextets = (bits + 5) / 6;
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

    std::string base64::decode_url(const std::string &data) {
        if (data.empty()) return {};
        // replace '+','/' to '-','_'
        constexpr char BASE64_CHARS[] =
                "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
        std::vector<int> decode_table(256, -1);
        for (int i = 0; i < 64; ++i) {
            decode_table[BASE64_CHARS[i]] = i;
        }
        decode_table['='] = 0;

        std::string decoded;
        size_t len = data.size();
        decoded.reserve((len * 3) / 4);

        uint32_t buffer = 0;
        int bits_collected = 0;

        for (size_t i = 0; i < len; ++i) {
            const char c = data[i];
            if (decode_table[c] < 0) continue;

            buffer = (buffer << 6) | decode_table[c];
            bits_collected += 6;

            if (bits_collected >= 8) {
                decoded.push_back(
                    static_cast<char>(
                        (buffer >> (bits_collected - 8)) & 0xFF));
                bits_collected -= 8;
            }
        }
        return decoded;
    }
}
