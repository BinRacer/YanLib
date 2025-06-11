/* clang-format off */
/*
 * @file rsa.h
 * @date 2025-04-12
 * @license MIT License
 *
 * Copyright (c) 2025 BinRacer <native.lab@outlook.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* clang-format on */
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
