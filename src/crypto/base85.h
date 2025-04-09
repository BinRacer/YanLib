//
// Created by forkernel on 2025/4/9.
//

#ifndef BASE85_H
#define BASE85_H
#include <vector>
#include <string>

namespace YanLib::crypto {
    class base85 {
    public:
        base85(const base85 &other) = delete;

        base85(base85 &&other) = delete;

        base85 &operator=(const base85 &other) = delete;

        base85 &operator=(base85 &&other) = delete;

        base85() = default;

        ~base85() = default;

        static std::vector<unsigned char> encode(const std::vector<unsigned char> &data);

        static std::vector<unsigned char> decode(const std::vector<unsigned char> &data);

        static std::string encode_string(const std::string &data);

        static std::string decode_string(const std::string &data);
    };
}

#endif //BASE85_H
