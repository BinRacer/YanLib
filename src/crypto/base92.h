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

        static std::vector<unsigned char> encode(const std::vector<unsigned char> &data);

        static std::vector<unsigned char> decode(const std::vector<unsigned char> &data);

        static std::string encode_string(const std::string &data);

        static std::string decode_string(const std::string &data);
    };
}
#endif //BASE92_H
