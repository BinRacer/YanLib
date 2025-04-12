//
// Created by forkernel on 2025/4/10.
//

#ifndef UUENCODE_H
#define UUENCODE_H
#include <vector>
#include <string>

namespace YanLib::crypto {
    class uuencode {
    public:
        uuencode(const uuencode &other) = delete;

        uuencode(uuencode &&other) = delete;

        uuencode &operator=(const uuencode &other) = delete;

        uuencode &operator=(uuencode &&other) = delete;

        uuencode() = default;

        ~uuencode() = default;

        static std::vector<uint8_t> encode(const std::vector<uint8_t> &data);

        static std::vector<uint8_t> decode(const std::vector<uint8_t> &data);

        static std::string encode_string(const std::string &data);

        static std::string decode_string(const std::string &data);
    };
}
#endif //UUENCODE_H
