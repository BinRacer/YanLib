//
// Created by forkernel on 2025/4/10.
//

#ifndef BASE100_H
#define BASE100_H
#include <vector>
#include <string>

namespace YanLib::crypto {
    class base100 {
    public:
        base100(const base100 &other) = delete;

        base100(base100 &&other) = delete;

        base100 &operator=(const base100 &other) = delete;

        base100 &operator=(base100 &&other) = delete;

        base100() = default;

        ~base100() = default;

        static std::vector<uint8_t> encode(const std::vector<uint8_t> &data);

        static std::vector<uint8_t> decode(const std::vector<uint8_t> &data);

        static std::string encode_string(const std::string &data);

        static std::string decode_string(const std::string &data);
    };
} // namespace YanLib::crypto
#endif // BASE100_H
