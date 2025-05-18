//
// Created by forkernel on 2025/4/10.
//

#ifndef BASE92_H
#define BASE92_H
#include <vector>
#include <string>

namespace YanLib::crypto {
    class base92 {
    public:
        base92(const base92 &other) = delete;

        base92(base92 &&other) = delete;

        base92 &operator=(const base92 &other) = delete;

        base92 &operator=(base92 &&other) = delete;

        base92() = default;

        ~base92() = default;

        static std::vector<uint8_t> encode(const std::vector<uint8_t> &data);

        static std::vector<uint8_t> decode(const std::vector<uint8_t> &data);

        static std::string encode_string(const std::string &data);

        static std::string decode_string(const std::string &data);
    };
} // namespace YanLib::crypto
#endif // BASE92_H
