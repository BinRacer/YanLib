//
// Created by forkernel on 2025/4/11.
//

#ifndef AES256_H
#define AES256_H
#include <Windows.h>
#include <string>
#include <vector>

namespace YanLib::crypto {
#ifndef AESPADDING
#define AESPADDING

    enum AES_PADDING {
        PKCS7_PADDING,
        ISO10126_PADDING,
        ANSI_X923_PADDING,
    };

    enum AES_MODE {
        MODE_CBC,
        MODE_ECB,
        // MODE_OFB,
        MODE_CFB,
        // MODE_CTS,
    };
#endif
    class aes256 {
    private:
        HCRYPTPROV crypt_prov_handle;
        HCRYPTHASH crypt_hash_handle;
        HCRYPTKEY crypt_key_handle;
        std::vector<uint8_t> data_bytes;
        bool is_done = false;
        DWORD error_code;

        struct KeyBlob {
            BLOBHEADER header;
            DWORD key_size;
            uint8_t key[32];
        };

        void cleanup();

        static std::string format_hex_fast(const std::vector<uint8_t> &data);

        static KeyBlob make_blob(const std::vector<uint8_t> &key);

        static void make_pkcs7_padding(std::vector<uint8_t> &data);

        static bool remove_pkcs7_padding(std::vector<uint8_t> &data,
                                         DWORD ret_len);

        static void make_iso10126_padding(std::vector<uint8_t> &data);

        static bool remove_iso10126_padding(std::vector<uint8_t> &data,
                                            DWORD ret_len);

        static void make_ansix923_padding(std::vector<uint8_t> &data);

        static bool remove_ansix923_padding(std::vector<uint8_t> &data,
                                            DWORD ret_len);

        bool pre_process(const std::vector<uint8_t> &key_bytes,
                         const std::vector<uint8_t> &iv,
                         AES_MODE mode);

        bool encode_process(std::vector<uint8_t> &data_bytes,
                            AES_PADDING padding);

        bool decode_process(std::vector<uint8_t> &data_bytes,
                            AES_PADDING padding);

    public:
        aes256(const aes256 &other) = delete;

        aes256(aes256 &&other) = delete;

        aes256 &operator=(const aes256 &other) = delete;

        aes256 &operator=(aes256 &&other) = delete;

        aes256();

        ~aes256();

        std::vector<uint8_t> encode_cbc(const std::vector<uint8_t> &data,
                                              const std::vector<uint8_t> &key,
                                              const std::vector<uint8_t> &iv,
                                              AES_PADDING padding = PKCS7_PADDING);

        std::vector<uint8_t> decode_cbc(const std::vector<uint8_t> &data,
                                              const std::vector<uint8_t> &key,
                                              const std::vector<uint8_t> &iv,
                                              AES_PADDING padding = PKCS7_PADDING);

        std::vector<uint8_t> encode_ecb(const std::vector<uint8_t> &data,
                                              const std::vector<uint8_t> &key,
                                              AES_PADDING padding = PKCS7_PADDING);

        std::vector<uint8_t> decode_ecb(const std::vector<uint8_t> &data,
                                              const std::vector<uint8_t> &key,
                                              AES_PADDING padding = PKCS7_PADDING);

        std::vector<uint8_t> encode_cfb(const std::vector<uint8_t> &data,
                                              const std::vector<uint8_t> &key,
                                              const std::vector<uint8_t> &iv,
                                              AES_PADDING padding = PKCS7_PADDING);

        std::vector<uint8_t> decode_cfb(const std::vector<uint8_t> &data,
                                              const std::vector<uint8_t> &key,
                                              const std::vector<uint8_t> &iv,
                                              AES_PADDING padding = PKCS7_PADDING);

        std::vector<uint8_t> generate_iv_bytes();

        std::string generate_iv_string();

        std::string hex_string() const;

        std::wstring hex_wstring() const;

        DWORD err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}
#endif //AES256_H
