//
// Created by forkernel on 2025/4/9.
//

#ifndef BASE32_H
#define BASE32_H
#include <string>
#include <vector>

namespace YanLib::crypto {
    class base32 {
    public:
        base32(const base32 &other) = delete;

        base32(base32 &&other) = delete;

        base32 &operator=(const base32 &other) = delete;

        base32 &operator=(base32 &&other) = delete;

        base32() = default;

        ~base32() = default;

        static std::vector<unsigned char> encode(const std::vector<unsigned char> &data);

        static std::vector<unsigned char> decode(const std::vector<unsigned char> &data);

        static std::string encode_string(const std::string &data);

        static std::string decode_string(const std::string &data);
    };
}
#endif //BASE32_H
