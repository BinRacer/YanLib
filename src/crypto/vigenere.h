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
    vigenere(const vigenere &other)            = delete;

    vigenere(vigenere &&other)                 = delete;

    vigenere &operator=(const vigenere &other) = delete;

    vigenere &operator=(vigenere &&other)      = delete;

    vigenere()                                 = default;

    ~vigenere()                                = default;

    static std::vector<uint8_t> encode(const std::vector<uint8_t> &data,
        const std::vector<uint8_t>                                &key);

    static std::vector<uint8_t> decode(const std::vector<uint8_t> &data,
        const std::vector<uint8_t>                                &key);

    static std::string encode_string(const std::string &data,
        const std::string                              &key);

    static std::string decode_string(const std::string &data,
        const std::string                              &key);
};
} // namespace YanLib::crypto
#endif // VIGENERE_H
