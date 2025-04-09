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
        base64(const base64 &other) = delete;

        base64(base64 &&other) = delete;

        base64 &operator=(const base64 &other) = delete;

        base64 &operator=(base64 &&other) = delete;

        base64() = default;

        ~base64() = default;

        static std::vector<unsigned char> encode(const unsigned char *data, size_t len);

        static std::vector<unsigned char> decode(const unsigned char *data, size_t len);

        static std::vector<unsigned char> encode(const std::vector<unsigned char> &data);

        static std::vector<unsigned char> decode(const std::vector<unsigned char> &data);

        static std::string encode_string(const std::string &data);

        static std::string decode_string(const std::string &data);

        static std::string encode_wstring(const std::wstring &data);

        static std::string decode_wstring(const std::wstring &data);

        static bool encode_file(const std::wstring &input_file,
                                const std::wstring &output_file);

        static bool decode_file(const std::wstring &input_file,
                                const std::wstring &output_file);

        static std::string encode_url(const std::string &data);

        static std::string decode_url(const std::string &data);
    };
}
#endif //BASE64_H
