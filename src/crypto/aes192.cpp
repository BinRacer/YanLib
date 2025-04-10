//
// Created by forkernel on 2025/4/11.
//

#include "aes192.h"
#include "../helper/convert.h"
#include <random>

namespace YanLib::crypto {
    aes192::aes192() {
        hCryptProv = 0;
        hCryptHash = 0;
        hCryptKey = 0;
        data_bytes = {};
        error_code = 0;
    }

    aes192::~aes192() {
        cleanup();
    }

    void aes192::cleanup() {
        if (hCryptKey) {
            CryptDestroyKey(hCryptKey);
            hCryptKey = 0;
        }
        if (hCryptHash) {
            CryptDestroyHash(hCryptHash);
            hCryptHash = 0;
        }
        if (hCryptProv) {
            CryptReleaseContext(hCryptProv, 0);
            hCryptProv = 0;
        }
    }

    std::string aes192::format_hex_fast(const std::vector<unsigned char> &data) {
        static constexpr char hexTable[] = "0123456789abcdef";
        std::string hexStr;
        hexStr.reserve(data.size() * 2);
        for (unsigned char byte: data) {
            hexStr += hexTable[byte >> 4];
            hexStr += hexTable[byte & 0x0F];
        }
        return hexStr;
    }

    aes192::KeyBlob aes192::make_blob(const std::vector<unsigned char> &key) {
        KeyBlob blob{};
        blob.header = {
            PLAINTEXTKEYBLOB,
            CUR_BLOB_VERSION,
            0,
            CALG_AES_192
        };
        blob.keySize = 24;
        memcpy(blob.key, key.data(), key.size());
        return blob;
    }

    void aes192::make_pkcs7_padding(std::vector<unsigned char> &data) {
        const size_t rawSize = data.size();
        const size_t padLen = 16 - (rawSize % 16);
        if (padLen == 0) {
            return;
        }
        data.insert(data.end(), padLen, static_cast<unsigned char>(padLen));
    }

    bool aes192::remove_pkcs7_padding(std::vector<unsigned char> &data,
                                      DWORD retLen) {
        do {
            if (data.empty() || retLen < 1 || retLen > data.size()) {
                break;
            }
            unsigned char pad_len = data[retLen - 1];
            if (pad_len < 1 || pad_len > 16) {
                break;
            }
            for (DWORD i = retLen - pad_len; i < retLen; i++) {
                if (data[i] != pad_len) {
                    return false;
                }
            }
            data.resize(retLen - pad_len);
            return true;
        } while (false);
        return false;
    }

    void aes192::make_iso10126_padding(std::vector<unsigned char> &data) {
        const size_t rawSize = data.size();
        const size_t padLen = 16 - (rawSize % 16);
        if (padLen == 0) {
            return;
        }
        std::random_device rd;
        for (int i = 0; i < padLen - 1; i++) {
            data.push_back(static_cast<unsigned char>(rd()));
        }
        data.push_back(static_cast<unsigned char>(padLen));
    }

    bool aes192::remove_iso10126_padding(std::vector<unsigned char> &data,
                                         DWORD retLen) {
        do {
            if (data.empty() || retLen < 1 || retLen > data.size()) {
                break;
            }
            unsigned char pad_len = data[retLen - 1];
            if (pad_len < 1 || pad_len > 16) {
                break;
            }
            data.resize(retLen - pad_len);
            return true;
        } while (false);
        return false;
    }

    void aes192::make_ansix923_padding(std::vector<unsigned char> &data) {
        const size_t rawSize = data.size();
        const size_t padLen = 16 - (rawSize % 16);
        if (padLen == 0) {
            return;
        }
        data.insert(data.end(), padLen - 1, 0);
        data.push_back(static_cast<unsigned char>(padLen));
    }

    bool aes192::remove_ansix923_padding(std::vector<unsigned char> &data,
                                         DWORD retLen) {
        do {
            if (data.empty() || retLen < 1 || retLen > data.size()) {
                break;
            }
            unsigned char pad_len = data[retLen - 1];
            if (pad_len < 1 || pad_len > 16) {
                break;
            }
            for (DWORD i = retLen - pad_len; i < retLen - 1; i++) {
                if (data[i] != 0) {
                    return false;
                }
            }
            data.resize(retLen - pad_len);
            return true;
        } while (false);
        return false;
    }

    bool aes192::pre_process(const std::vector<unsigned char> &key_bytes,
                             const std::vector<unsigned char> &iv,
                             AES_MODE mode) {
        do {
            wchar_t provider[] =
                    L"Microsoft Enhanced RSA and AES Cryptographic Provider";
            if (!CryptAcquireContextW(&hCryptProv,
                                      nullptr,
                                      provider,
                                      PROV_RSA_AES,
                                      CRYPT_VERIFYCONTEXT)) {
                error_code = GetLastError();
                break;
            }

            KeyBlob blob = make_blob(key_bytes);
            if (!CryptImportKey(hCryptProv,
                                reinterpret_cast<unsigned char *>(&blob),
                                sizeof(blob),
                                0,
                                0,
                                &hCryptKey)) {
                error_code = GetLastError();
                break;
            }
            DWORD aes_mode = 0;
            switch (mode) {
                case MODE_CBC:
                    aes_mode = CRYPT_MODE_CBC;
                    break;
                case MODE_ECB:
                    aes_mode = CRYPT_MODE_ECB;
                    break;
                // case MODE_OFB:
                //     aes_mode = CRYPT_MODE_OFB;
                //     break;
                case MODE_CFB:
                    aes_mode = CRYPT_MODE_CFB;
                    break;
                // case MODE_CTS:
                //     aes_mode = CRYPT_MODE_CTS;
                //     break;
                default:
                    aes_mode = CRYPT_MODE_CBC;
            }

            if (!CryptSetKeyParam(hCryptKey,
                                  KP_MODE,
                                  reinterpret_cast<unsigned char *>(&aes_mode),
                                  0)) {
                error_code = GetLastError();
                break;
            }
            if (mode != MODE_ECB) {
                unsigned char localIV[16];
                memcpy(localIV, iv.data(), 16);
                if (!CryptSetKeyParam(hCryptKey,
                                      KP_IV,
                                      localIV,
                                      0)) {
                    error_code = GetLastError();
                    break;
                }
            }
            return true;
        } while (false);
        return false;
    }

    bool aes192::encode_process(std::vector<unsigned char> &data_bytes,
                                AES_PADDING padding) {
        do {
            switch (padding) {
                case PKCS7_PADDING:
                    make_pkcs7_padding(data_bytes);
                    break;
                case ISO10126_PADDING:
                    make_iso10126_padding(data_bytes);
                    break;
                case ANSI_X923_PADDING:
                    make_ansix923_padding(data_bytes);
                    break;
                default:
                    make_pkcs7_padding(data_bytes);
            }
            DWORD dataSize = data_bytes.size();
            DWORD rawSize = data_bytes.size();
            if (!CryptEncrypt(hCryptKey,
                              0,
                              FALSE,
                              0,
                              data_bytes.data(),
                              &dataSize,
                              0)) {
                error_code = GetLastError();
                if (error_code == ERROR_MORE_DATA) {
                    data_bytes.resize(dataSize);
                    if (!CryptEncrypt(hCryptKey,
                                      0,
                                      FALSE,
                                      0,
                                      data_bytes.data(),
                                      &rawSize,
                                      data_bytes.size())) {
                        error_code = GetLastError();
                        break;
                    }
                } else {
                    break;
                }
            }
            cleanup();
            return true;
        } while (false);
        cleanup();
        return false;
    }

    bool aes192::decode_process(std::vector<unsigned char> &data_bytes,
                                AES_PADDING padding) {
        do {
            DWORD dataSize = data_bytes.size();
            if (!CryptDecrypt(hCryptKey,
                              0,
                              FALSE,
                              0,
                              data_bytes.data(),
                              &dataSize)) {
                error_code = GetLastError();
                break;
            }
            bool isFalse = false;
            switch (padding) {
                case PKCS7_PADDING:
                    if (!remove_pkcs7_padding(data_bytes, dataSize)) {
                        isFalse = true;
                    }
                    break;
                case ISO10126_PADDING:
                    if (!remove_iso10126_padding(data_bytes, dataSize)) {
                        isFalse = true;
                    }
                    break;
                case ANSI_X923_PADDING:
                    if (!remove_ansix923_padding(data_bytes, dataSize)) {
                        isFalse = true;
                    }
                    break;
                default:
                    if (!remove_pkcs7_padding(data_bytes, dataSize)) {
                        isFalse = true;
                    }
            }
            if (isFalse) {
                break;
            }
            cleanup();
            return true;
        } while (false);
        cleanup();
        return false;
    }

    std::vector<unsigned char> aes192::encode_cbc(const std::vector<unsigned char> &data,
                                                  const std::vector<unsigned char> &key,
                                                  const std::vector<unsigned char> &iv,
                                                  AES_PADDING padding) {
        if (data.empty() ||
            key.empty() ||
            iv.empty() ||
            key.size() != 24 ||
            iv.size() != 16) {
            return {};
        }
        do {
            data_bytes.resize(data.size());
            memcpy(data_bytes.data(), data.data(), data.size());
            std::vector<unsigned char> key_bytes(key.begin(), key.end());
            std::vector<unsigned char> localIV(iv.begin(), iv.end());
            if (!pre_process(key_bytes, localIV, MODE_CBC)) {
                break;
            }
            if (!encode_process(data_bytes, padding)) {
                break;
            }
            isDone = true;
            return data_bytes;
        } while (false);
        return {};
    }

    std::vector<unsigned char> aes192::decode_cbc(const std::vector<unsigned char> &data,
                                                  const std::vector<unsigned char> &key,
                                                  const std::vector<unsigned char> &iv,
                                                  AES_PADDING padding) {
        if (data.empty() ||
            key.empty() ||
            iv.empty() ||
            key.size() != 24 ||
            iv.size() != 16) {
            return {};
        }
        do {
            data_bytes.resize(data.size());
            memcpy(data_bytes.data(), data.data(), data.size());
            std::vector<unsigned char> key_bytes(key.begin(), key.end());
            std::vector<unsigned char> localIV(iv.begin(), iv.end());
            if (!pre_process(key_bytes, localIV, MODE_CBC)) {
                break;
            }
            if (!decode_process(data_bytes, padding)) {
                break;
            }
            isDone = true;
            return data_bytes;
        } while (false);
        return {};
    }

    std::vector<unsigned char> aes192::encode_ecb(const std::vector<unsigned char> &data,
                                                  const std::vector<unsigned char> &key,
                                                  AES_PADDING padding) {
        if (data.empty() ||
            key.empty() ||
            key.size() != 24) {
            return {};
        }
        do {
            data_bytes.resize(data.size());
            memcpy(data_bytes.data(), data.data(), data.size());
            std::vector<unsigned char> key_bytes(key.begin(), key.end());
            std::vector<unsigned char> iv;
            if (!pre_process(key_bytes, iv, MODE_ECB)) {
                break;
            }
            if (!encode_process(data_bytes, padding)) {
                break;
            }
            isDone = true;
            return data_bytes;
        } while (false);
        return {};
    }

    std::vector<unsigned char> aes192::decode_ecb(const std::vector<unsigned char> &data,
                                                  const std::vector<unsigned char> &key,
                                                  AES_PADDING padding) {
        if (data.empty() ||
            key.empty() ||
            key.size() != 24) {
            return {};
        }
        do {
            data_bytes.resize(data.size());
            memcpy(data_bytes.data(), data.data(), data.size());
            std::vector<unsigned char> key_bytes(key.begin(), key.end());
            std::vector<unsigned char> iv;
            if (!pre_process(key_bytes, iv, MODE_ECB)) {
                break;
            }
            if (!decode_process(data_bytes, padding)) {
                break;
            }
            isDone = true;
            return data_bytes;
        } while (false);
        return {};
    }

    std::vector<unsigned char> aes192::encode_cfb(const std::vector<unsigned char> &data,
                                                  const std::vector<unsigned char> &key,
                                                  const std::vector<unsigned char> &iv,
                                                  AES_PADDING padding) {
        if (data.empty() ||
            key.empty() ||
            iv.empty() ||
            key.size() != 24 ||
            iv.size() != 16) {
            return {};
        }
        do {
            data_bytes.resize(data.size());
            memcpy(data_bytes.data(), data.data(), data.size());
            std::vector<unsigned char> key_bytes(key.begin(), key.end());
            std::vector<unsigned char> localIV(iv.begin(), iv.end());
            if (!pre_process(key_bytes, localIV, MODE_CFB)) {
                break;
            }
            if (!encode_process(data_bytes, padding)) {
                break;
            }
            isDone = true;
            return data_bytes;
        } while (false);
        return {};
    }

    std::vector<unsigned char> aes192::decode_cfb(const std::vector<unsigned char> &data,
                                                  const std::vector<unsigned char> &key,
                                                  const std::vector<unsigned char> &iv,
                                                  AES_PADDING padding) {
        if (data.empty() ||
            key.empty() ||
            iv.empty() ||
            key.size() != 24 ||
            iv.size() != 16) {
            return {};
        }
        do {
            data_bytes.resize(data.size());
            memcpy(data_bytes.data(), data.data(), data.size());
            std::vector<unsigned char> key_bytes(key.begin(), key.end());
            std::vector<unsigned char> localIV(iv.begin(), iv.end());
            if (!pre_process(key_bytes, localIV, MODE_CFB)) {
                break;
            }
            if (!decode_process(data_bytes, padding)) {
                break;
            }
            isDone = true;
            return data_bytes;
        } while (false);
        return {};
    }

    std::vector<unsigned char> aes192::generate_iv_bytes() {
        do {
            wchar_t provider[] =
                    L"Microsoft Enhanced RSA and AES Cryptographic Provider";
            if (!CryptAcquireContextW(&hCryptProv,
                                      nullptr,
                                      provider,
                                      PROV_RSA_AES,
                                      CRYPT_VERIFYCONTEXT)) {
                error_code = GetLastError();
                break;
            }
            std::vector<unsigned char> iv(16, 0);
            if (!CryptGenRandom(hCryptProv, iv.size(), iv.data())) {
                break;
            }
            if (hCryptProv) {
                CryptReleaseContext(hCryptProv, 0);
                hCryptProv = 0;
            }
            return iv;
        } while (false);
        return {};
    }

    std::string aes192::generate_iv_string() {
        std::vector<unsigned char> iv = generate_iv_bytes();
        std::string result(iv.begin(), iv.end());
        return result;
    }

    std::string aes192::hex_string() const {
        if (isDone) {
            return format_hex_fast(data_bytes);
        }
        return {};
    }

    std::wstring aes192::hex_wstring() const {
        return helper::convert::str_to_wstr(hex_string());
    }

    DWORD aes192::err_code() const {
        return error_code;
    }

    std::string aes192::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring aes192::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
