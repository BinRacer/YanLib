//
// Created by forkernel on 2025/4/9.
//

#ifndef BASE64_H
#define BASE64_H
#include <string>
#include <vector>

namespace YanLib::crypto {
class base64 {
public:
    base64(const base64 &other)            = delete;

    base64(base64 &&other)                 = delete;

    base64 &operator=(const base64 &other) = delete;

    base64 &operator=(base64 &&other)      = delete;

    base64()                               = default;

    ~base64()                              = default;

    static std::vector<uint8_t> encode(const uint8_t *data, size_t len);

    static std::vector<uint8_t> decode(const uint8_t *data, size_t len);

    static std::vector<uint8_t> encode(const std::vector<uint8_t> &data);

    static std::vector<uint8_t> decode(const std::vector<uint8_t> &data);

    static std::string encode_string(const std::string &data);

    static std::string decode_string(const std::string &data);

    static bool encode_file(const std::string &input_file,
        const std::string                     &output_file);

    static bool encode_file(const std::wstring &input_file,
        const std::wstring                     &output_file);

    static bool decode_file(const std::string &input_file,
        const std::string                     &output_file);

    static bool decode_file(const std::wstring &input_file,
        const std::wstring                     &output_file);

    static std::vector<uint8_t> encode_url(const uint8_t *data, size_t len);

    static std::vector<uint8_t> decode_url(const uint8_t *data, size_t len);

    static std::vector<uint8_t> encode_url(const std::vector<uint8_t> &data);

    static std::vector<uint8_t> decode_url(const std::vector<uint8_t> &data);

    static std::string encode_url(const std::string &data);

    static std::string decode_url(const std::string &data);
};
} // namespace YanLib::crypto
#endif // BASE64_H
