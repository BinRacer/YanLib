//
// Created by forkernel on 2025/4/9.
//

#ifndef BASE91_H
#define BASE91_H
#include <vector>
#include <string>

namespace YanLib::crypto {
class base91 {
public:
    base91(const base91 &other)            = delete;

    base91(base91 &&other)                 = delete;

    base91 &operator=(const base91 &other) = delete;

    base91 &operator=(base91 &&other)      = delete;

    base91()                               = default;

    ~base91()                              = default;

    static std::vector<uint8_t> encode(const std::vector<uint8_t> &data);

    static std::vector<uint8_t> decode(const std::vector<uint8_t> &data);

    static std::string encode_string(const std::string &data);

    static std::string decode_string(const std::string &data);
};
} // namespace YanLib::crypto

#endif // BASE91_H
