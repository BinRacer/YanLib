//
// Created by forkernel on 2025/4/10.
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

        static std::vector<unsigned char> encode(const std::vector<unsigned char> &data);

        static std::vector<unsigned char> decode(const std::vector<unsigned char> &data);

        static std::string encode_string(const std::string &data);

        static std::string decode_string(const std::string &data);
    };
}
#endif //XXENCODE_H
