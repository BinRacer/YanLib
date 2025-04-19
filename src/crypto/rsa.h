//
// Created by forkernel on 2025/4/12.
//

#ifndef RSA_H
#define RSA_H
#include <Windows.h>
#include <string>
#include <vector>

namespace YanLib::crypto {
#ifndef RSABITSLENGTH
#define RSABITSLENGTH

    enum RSA_KEY_LENGTH {
        RSA_384BIT_KEY = 0x01800000, // 384 bits
        RSA_512BIT_KEY = 0x02000000, // 512 bits
        RSA_768BIT_KEY = 0x03000000, // 768 bits
        RSA_1024BIT_KEY = 0x04000000, // 1024 bits
        RSA_1536BIT_KEY = 0x06000000, // 1536 bits
        RSA_2048BIT_KEY = 0x08000000, // 2048 bits
        RSA_3072BIT_KEY = 0x0C000000, // 3072 bits
        RSA_4096BIT_KEY = 0x10000000, // 4096 bits
        RSA_8192BIT_KEY = 0x20000000, // 8192 bits
        RSA_16384BIT_KEY = 0x40000000 // 16,384 bits
    };
#endif
    class rsa {
    private:
        HCRYPTPROV crypt_prov_handle = 0;
        HCRYPTKEY crypt_key_handle = 0;
        std::vector<uint8_t> pub_key{};
        std::vector<uint8_t> priv_key{};
        DWORD error_code = 0;

        void cleanup();

        static std::string format_hex_fast(const std::vector<uint8_t> &data);

    public:
        rsa(const rsa &other) = delete;

        rsa(rsa &&other) = delete;

        rsa &operator=(const rsa &other) = delete;

        rsa &operator=(rsa &&other) = delete;

        rsa() = default;

        ~rsa();

        bool generate_key(RSA_KEY_LENGTH key_length = RSA_4096BIT_KEY);

        std::vector<uint8_t> encode(const std::vector<uint8_t> &data,
                                    const std::vector<uint8_t> &pub_blob);

        std::vector<uint8_t> decode(const std::vector<uint8_t> &data,
                                    const std::vector<uint8_t> &priv_blob);

        std::string encode_to_base64(const std::vector<uint8_t> &data,
                                     const std::vector<uint8_t> &pub_blob);

        std::string decode_to_base64(const std::vector<uint8_t> &data,
                                     const std::vector<uint8_t> &priv_blob);

        std::vector<uint8_t> pub_blob() const;

        std::vector<uint8_t> priv_blob() const;

        std::string pub_hex() const;

        std::string priv_hex() const;

        std::string pub_base64() const;

        std::string priv_base64() const;

        std::string pub_pem() const;

        std::string priv_pem() const;

        DWORD err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}
#endif //RSA_H
