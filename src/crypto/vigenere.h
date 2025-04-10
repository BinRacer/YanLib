//
// Created by forkernel on 2025/4/10.
//

#ifndef VIGENERE_H
#define VIGENERE_H
#include <vector>
#include <string>

namespace YanLib::crypto {
    class vigenere {
    public:
        vigenere(const vigenere &other) = delete;

        vigenere(vigenere &&other) = delete;

        vigenere &operator=(const vigenere &other) = delete;

        vigenere &operator=(vigenere &&other) = delete;

        vigenere() = default;

        ~vigenere() = default;

        static std::vector<unsigned char> encode(const std::vector<unsigned char> &data,
                                                 const std::vector<unsigned char> &key);

        static std::vector<unsigned char> decode(const std::vector<unsigned char> &data,
                                                 const std::vector<unsigned char> &key);

        static std::string encode_string(const std::string &data,
                                         const std::string &key);

        static std::string decode_string(const std::string &data,
                                         const std::string &key);
    };
}
#endif //VIGENERE_H
