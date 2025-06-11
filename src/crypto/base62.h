//
// Created by BinRacer <native.lab@outlook.com> on 2025/4/9.
//

#ifndef BASE62_H
#define BASE62_H
#include <string>
#include <vector>

namespace YanLib::crypto {
    class base62 {
    public:
        base62(const base62 &other) = delete;

        base62(base62 &&other) = delete;

        base62 &operator=(const base62 &other) = delete;

        base62 &operator=(base62 &&other) = delete;

        base62() = default;

        ~base62() = default;

        static std::vector<uint8_t> encode(const std::vector<uint8_t> &data);

        static std::vector<uint8_t> decode(const std::vector<uint8_t> &data);

        static std::string encode_string(const std::string &data);

        static std::string decode_string(const std::string &data);
    };
} // namespace YanLib::crypto

#endif // BASE62_H
