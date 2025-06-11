/* clang-format off */
/*
 * @file aes.h
 * @date 2025-04-10
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
#ifndef AES_H
#define AES_H
#include <Windows.h>
#include <string>
#include <vector>

namespace YanLib::crypto {
#ifndef AESPADDING
#define AESPADDING

    enum class AesPadding : uint8_t {
        PKCS7,
        ISO10126,
        ANSIX923,
    };
#endif
#ifndef AESMODE
#define AESMODE

    enum class AesMode : uint32_t {
        CBC = CRYPT_MODE_CBC,
        ECB = CRYPT_MODE_ECB,
        // OFB = CRYPT_OFB,
        CFB = CRYPT_MODE_CFB,
        // CTS = CRYPT_CTS,
    };
#endif
    class aes {
    private:
        HCRYPTPROV crypt_prov_handle;
        HCRYPTHASH crypt_hash_handle;
        HCRYPTKEY crypt_key_handle;
        std::vector<uint8_t> data_bytes;
        bool is_done = false;
        uint32_t error_code;

        struct KeyBlob {
            BLOBHEADER header;
            uint32_t key_size;
            uint8_t key[16];
        };

        void cleanup();

        static std::string format_hex_fast(const std::vector<uint8_t> &data);

        static KeyBlob make_blob(const std::vector<uint8_t> &key);

        static void make_pkcs7_padding(std::vector<uint8_t> &data);

        static bool remove_pkcs7_padding(std::vector<uint8_t> &data,
                                         uint32_t real_size);

        static void make_iso10126_padding(std::vector<uint8_t> &data);

        static bool remove_iso10126_padding(std::vector<uint8_t> &data,
                                            uint32_t real_size);

        static void make_ansix923_padding(std::vector<uint8_t> &data);

        static bool remove_ansix923_padding(std::vector<uint8_t> &data,
                                            uint32_t real_size);

        bool pre_process(const std::vector<uint8_t> &key_bytes,
                         const std::vector<uint8_t> &iv,
                         AesMode mode);

        bool encode_process(std::vector<uint8_t> &data_bytes,
                            AesPadding padding);

        bool decode_process(std::vector<uint8_t> &data_bytes,
                            AesPadding padding);

    public:
        aes(const aes &other) = delete;

        aes(aes &&other) = delete;

        aes &operator=(const aes &other) = delete;

        aes &operator=(aes &&other) = delete;

        aes();

        ~aes();

        std::vector<uint8_t> encode_cbc(const std::vector<uint8_t> &data,
                                        const std::vector<uint8_t> &key,
                                        const std::vector<uint8_t> &iv,
                                        AesPadding padding = AesPadding::PKCS7);

        std::vector<uint8_t> decode_cbc(const std::vector<uint8_t> &data,
                                        const std::vector<uint8_t> &key,
                                        const std::vector<uint8_t> &iv,
                                        AesPadding padding = AesPadding::PKCS7);

        std::vector<uint8_t> encode_ecb(const std::vector<uint8_t> &data,
                                        const std::vector<uint8_t> &key,
                                        AesPadding padding = AesPadding::PKCS7);

        std::vector<uint8_t> decode_ecb(const std::vector<uint8_t> &data,
                                        const std::vector<uint8_t> &key,
                                        AesPadding padding = AesPadding::PKCS7);

        std::vector<uint8_t> encode_cfb(const std::vector<uint8_t> &data,
                                        const std::vector<uint8_t> &key,
                                        const std::vector<uint8_t> &iv,
                                        AesPadding padding = AesPadding::PKCS7);

        std::vector<uint8_t> decode_cfb(const std::vector<uint8_t> &data,
                                        const std::vector<uint8_t> &key,
                                        const std::vector<uint8_t> &iv,
                                        AesPadding padding = AesPadding::PKCS7);

        std::vector<uint8_t> generate_iv_bytes();

        std::string generate_iv_string();

        [[nodiscard]] std::string hex_string() const;

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::crypto
#endif // AES_H
