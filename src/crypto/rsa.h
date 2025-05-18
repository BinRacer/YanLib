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

    enum class RsaKeyBits : uint32_t {
        Bit384 = 0x01800000,  // 384 bits
        Bit512 = 0x02000000,  // 512 bits
        Bit768 = 0x03000000,  // 768 bits
        Bit1024 = 0x04000000, // 1024 bits
        Bit1536 = 0x06000000, // 1536 bits
        Bit2048 = 0x08000000, // 2048 bits
        Bit3072 = 0x0C000000, // 3072 bits
        Bit4096 = 0x10000000, // 4096 bits
        Bit8192 = 0x20000000, // 8192 bits
        Bit16384 = 0x40000000 // 16,384 bits
    };
#endif
    class rsa {
    private:
        HCRYPTPROV crypt_prov_handle = 0;
        HCRYPTKEY crypt_key_handle = 0;
        std::vector<uint8_t> pub_key{};
        std::vector<uint8_t> priv_key{};
        uint32_t error_code = 0;

        void cleanup();

        static std::string format_hex_fast(const std::vector<uint8_t> &data);

    public:
        rsa(const rsa &other) = delete;

        rsa(rsa &&other) = delete;

        rsa &operator=(const rsa &other) = delete;

        rsa &operator=(rsa &&other) = delete;

        rsa() = default;

        ~rsa();

        bool generate_key(RsaKeyBits key_bits = RsaKeyBits::Bit4096);

        std::vector<uint8_t> encode(const std::vector<uint8_t> &data,
                                    const std::vector<uint8_t> &pub_blob);

        std::vector<uint8_t> decode(const std::vector<uint8_t> &data,
                                    const std::vector<uint8_t> &priv_blob);

        std::vector<uint8_t>
        encode_to_base64(const std::vector<uint8_t> &data,
                         const std::vector<uint8_t> &pub_blob);

        std::vector<uint8_t>
        decode_from_base64(const std::vector<uint8_t> &data,
                           const std::vector<uint8_t> &priv_blob);

        [[nodiscard]] std::vector<uint8_t> pub_blob() const;

        [[nodiscard]] std::vector<uint8_t> priv_blob() const;

        [[nodiscard]] std::string pub_hex() const;

        [[nodiscard]] std::string priv_hex() const;

        [[nodiscard]] std::string pub_base64() const;

        [[nodiscard]] std::string priv_base64() const;

        [[nodiscard]] std::string pub_pem() const;

        [[nodiscard]] std::string priv_pem() const;

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::crypto
#endif // RSA_H
