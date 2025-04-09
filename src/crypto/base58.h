//
// Created by forkernel on 2025/4/9.
//

#ifndef BASE58_H
#define BASE58_H
#include <string>
#include <vector>

namespace YanLib::crypto {
    class base58 {
    public:
        base58(const base58 &other) = delete;

        base58(base58 &&other) = delete;

        base58 &operator=(const base58 &other) = delete;

        base58 &operator=(base58 &&other) = delete;

        base58() = default;

        ~base58() = default;

        static std::vector<unsigned char> encode(const std::vector<unsigned char> &data);

        static std::vector<unsigned char> decode(const std::vector<unsigned char> &data);

        static std::string encode_string(const std::string &data);

        static std::string decode_string(const std::string &data);
    };
}
#endif //BASE58_H
