//
// Created by BinRacer <native.lab@outlook.com> on 2025/4/10.
//

#ifndef XXENCODE_H
#define XXENCODE_H
#include <vector>
#include <string>

namespace YanLib::crypto {
    class xxencode {
    public:
        xxencode(const xxencode &other) = delete;

        xxencode(xxencode &&other) = delete;

        xxencode &operator=(const xxencode &other) = delete;

        xxencode &operator=(xxencode &&other) = delete;

        xxencode() = default;

        ~xxencode() = default;

        static std::vector<uint8_t> encode(const std::vector<uint8_t> &data);

        static std::vector<uint8_t> decode(const std::vector<uint8_t> &data);

        static std::string encode_string(const std::string &data);

        static std::string decode_string(const std::string &data);
    };
} // namespace YanLib::crypto
#endif // XXENCODE_H
