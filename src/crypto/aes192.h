//
// Created by forkernel on 2025/4/11.
//

#ifndef AES192_H
#define AES192_H
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
    class aes192 {
    private:
        HCRYPTPROV hCryptProv;
        HCRYPTHASH hCryptHash;
        HCRYPTKEY hCryptKey;
        std::vector<unsigned char> data_bytes;
        bool isDone = false;
        DWORD error_code;

        struct KeyBlob {
            BLOBHEADER header;
            DWORD keySize;
            unsigned char key[24];
        };

        void cleanup();

        static std::string format_hex_fast(const std::vector<unsigned char> &data);

        static KeyBlob make_blob(const std::vector<unsigned char> &key);

        static void make_pkcs7_padding(std::vector<unsigned char> &data);

        static bool remove_pkcs7_padding(std::vector<unsigned char> &data,
                                         DWORD retLen);

        static void make_iso10126_padding(std::vector<unsigned char> &data);

        static bool remove_iso10126_padding(std::vector<unsigned char> &data,
                                            DWORD retLen);

        static void make_ansix923_padding(std::vector<unsigned char> &data);

        static bool remove_ansix923_padding(std::vector<unsigned char> &data,
                                            DWORD retLen);

        bool pre_process(const std::vector<unsigned char> &key_bytes,
                         const std::vector<unsigned char> &iv,
                         AES_MODE mode);

        bool encode_process(std::vector<unsigned char> &data_bytes,
                            AES_PADDING padding);

        bool decode_process(std::vector<unsigned char> &data_bytes,
                            AES_PADDING padding);

    public:
        aes192(const aes192 &other) = delete;

        aes192(aes192 &&other) = delete;

        aes192 &operator=(const aes192 &other) = delete;

        aes192 &operator=(aes192 &&other) = delete;

        aes192();

        ~aes192();

        std::vector<unsigned char> encode_cbc(const std::vector<unsigned char> &data,
                                              const std::vector<unsigned char> &key,
                                              const std::vector<unsigned char> &iv,
                                              AES_PADDING padding = PKCS7_PADDING);

        std::vector<unsigned char> decode_cbc(const std::vector<unsigned char> &data,
                                              const std::vector<unsigned char> &key,
                                              const std::vector<unsigned char> &iv,
                                              AES_PADDING padding = PKCS7_PADDING);

        std::vector<unsigned char> encode_ecb(const std::vector<unsigned char> &data,
                                              const std::vector<unsigned char> &key,
                                              AES_PADDING padding = PKCS7_PADDING);

        std::vector<unsigned char> decode_ecb(const std::vector<unsigned char> &data,
                                              const std::vector<unsigned char> &key,
                                              AES_PADDING padding = PKCS7_PADDING);

        std::vector<unsigned char> encode_cfb(const std::vector<unsigned char> &data,
                                              const std::vector<unsigned char> &key,
                                              const std::vector<unsigned char> &iv,
                                              AES_PADDING padding = PKCS7_PADDING);

        std::vector<unsigned char> decode_cfb(const std::vector<unsigned char> &data,
                                              const std::vector<unsigned char> &key,
                                              const std::vector<unsigned char> &iv,
                                              AES_PADDING padding = PKCS7_PADDING);

        std::vector<unsigned char> generate_iv_bytes();

        std::string generate_iv_string();

        std::string hex_string() const;

        std::wstring hex_wstring() const;

        DWORD err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}
#endif //AES192_H
