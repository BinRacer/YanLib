//
// Created by forkernel on 2025/4/9.
//

#ifndef BASE16_H
#define BASE16_H
#include <string>
#include <vector>

namespace YanLib::crypto {
    class base16 {
    public:
        base16(const base16 &other) = delete;

        base16(base16 &&other) = delete;

        base16 &operator=(const base16 &other) = delete;

        base16 &operator=(base16 &&other) = delete;

        base16() = default;

        ~base16() = default;

        static std::vector<uint8_t> encode(const std::vector<uint8_t> &data);

        static std::vector<uint8_t> decode(const std::vector<uint8_t> &data);

        static std::string encode_string(const std::string &data);

        static std::string decode_string(const std::string &data);
    };
} // namespace YanLib::crypto

#endif // BASE16_H
