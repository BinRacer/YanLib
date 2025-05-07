//
// Created by forkernel on 2025/4/11.
//

#include "aes256.h"
#include "helper/convert.h"
#include <random>

namespace YanLib::crypto {
    aes256::aes256() {
        crypt_prov_handle = 0;
        crypt_hash_handle = 0;
        crypt_key_handle = 0;
        data_bytes = {};
        error_code = 0;
    }

    aes256::~aes256() {
        cleanup();
    }

    void aes256::cleanup() {
        if (crypt_key_handle) {
            CryptDestroyKey(crypt_key_handle);
            crypt_key_handle = 0;
        }
        if (crypt_hash_handle) {
            CryptDestroyHash(crypt_hash_handle);
            crypt_hash_handle = 0;
        }
        if (crypt_prov_handle) {
            CryptReleaseContext(crypt_prov_handle, 0);
            crypt_prov_handle = 0;
        }
    }

    std::string aes256::format_hex_fast(const std::vector<uint8_t> &data) {
        static constexpr char hex_table[] = "0123456789abcdef";
        std::string hex_str;
        hex_str.reserve(data.size() * 2);
        for (uint8_t byte: data) {
            hex_str += hex_table[byte >> 4];
            hex_str += hex_table[byte & 0x0F];
        }
        return hex_str;
    }

    aes256::KeyBlob aes256::make_blob(const std::vector<uint8_t> &key) {
        KeyBlob blob{};
        blob.header = {
            PLAINTEXTKEYBLOB,
            CUR_BLOB_VERSION,
            0,
            CALG_AES_256
        };
        blob.key_size = 32;
        memcpy(blob.key, key.data(), key.size());
        return blob;
    }

    void aes256::make_pkcs7_padding(std::vector<uint8_t> &data) {
        const size_t raw_size = data.size();
        const size_t pad_len = 16 - (raw_size % 16);
        if (pad_len == 0) {
            return;
        }
        data.insert(data.end(), pad_len, static_cast<uint8_t>(pad_len));
    }

    bool aes256::remove_pkcs7_padding(std::vector<uint8_t> &data,
                                      unsigned long ret_len) {
        do {
            if (data.empty() || ret_len < 1 || ret_len > data.size()) {
                break;
            }
            uint8_t pad_len = data[ret_len - 1];
            if (pad_len < 1 || pad_len > 16) {
                break;
            }
            for (unsigned long i = ret_len - pad_len; i < ret_len; i++) {
                if (data[i] != pad_len) {
                    return false;
                }
            }
            data.resize(ret_len - pad_len);
            return true;
        } while (false);
        return false;
    }

    void aes256::make_iso10126_padding(std::vector<uint8_t> &data) {
        const size_t raw_size = data.size();
        const size_t pad_len = 16 - (raw_size % 16);
        if (pad_len == 0) {
            return;
        }
        std::random_device rd = {};
        for (int32_t i = 0; i < pad_len - 1; i++) {
            data.push_back(static_cast<uint8_t>(rd()));
        }
        data.push_back(static_cast<uint8_t>(pad_len));
    }

    bool aes256::remove_iso10126_padding(std::vector<uint8_t> &data,
                                         unsigned long ret_len) {
        do {
            if (data.empty() || ret_len < 1 || ret_len > data.size()) {
                break;
            }
            uint8_t pad_len = data[ret_len - 1];
            if (pad_len < 1 || pad_len > 16) {
                break;
            }
            data.resize(ret_len - pad_len);
            return true;
        } while (false);
        return false;
    }

    void aes256::make_ansix923_padding(std::vector<uint8_t> &data) {
        const size_t raw_size = data.size();
        const size_t pad_len = 16 - (raw_size % 16);
        if (pad_len == 0) {
            return;
        }
        data.insert(data.end(), pad_len - 1, 0);
        data.push_back(static_cast<uint8_t>(pad_len));
    }

    bool aes256::remove_ansix923_padding(std::vector<uint8_t> &data,
                                         unsigned long ret_len) {
        do {
            if (data.empty() || ret_len < 1 || ret_len > data.size()) {
                break;
            }
            uint8_t pad_len = data[ret_len - 1];
            if (pad_len < 1 || pad_len > 16) {
                break;
            }
            for (unsigned long i = ret_len - pad_len; i < ret_len - 1; i++) {
                if (data[i] != 0) {
                    return false;
                }
            }
            data.resize(ret_len - pad_len);
            return true;
        } while (false);
        return false;
    }

    bool aes256::pre_process(const std::vector<uint8_t> &key_bytes,
                             const std::vector<uint8_t> &iv,
                             AesMode mode) {
        do {
            wchar_t provider[] =
                    L"Microsoft Enhanced RSA and AES Cryptographic Provider";
            if (!CryptAcquireContextW(&crypt_prov_handle,
                                      nullptr,
                                      provider,
                                      PROV_RSA_AES,
                                      CRYPT_VERIFYCONTEXT)) {
                error_code = GetLastError();
                break;
            }

            KeyBlob blob = make_blob(key_bytes);
            if (!CryptImportKey(crypt_prov_handle,
                                reinterpret_cast<uint8_t *>(&blob),
                                sizeof(blob),
                                0,
                                0,
                                &crypt_key_handle)) {
                error_code = GetLastError();
                break;
            }
            auto aes_mode = static_cast<unsigned long>(mode);
            if (!CryptSetKeyParam(crypt_key_handle,
                                  KP_MODE,
                                  reinterpret_cast<uint8_t *>(&aes_mode),
                                  0)) {
                error_code = GetLastError();
                break;
            }
            if (mode != AesMode::MODE_ECB) {
                uint8_t local_iv[16];
                memcpy(local_iv, iv.data(), 16);
                if (!CryptSetKeyParam(crypt_key_handle,
                                      KP_IV,
                                      local_iv,
                                      0)) {
                    error_code = GetLastError();
                    break;
                }
            }
            return true;
        } while (false);
        return false;
    }

    bool aes256::encode_process(std::vector<uint8_t> &data_bytes,
                                AesPadding padding) {
        do {
            switch (padding) {
                case AesPadding::PKCS7_PADDING:
                    make_pkcs7_padding(data_bytes);
                    break;
                case AesPadding::ISO10126_PADDING:
                    make_iso10126_padding(data_bytes);
                    break;
                case AesPadding::ANSI_X923_PADDING:
                    make_ansix923_padding(data_bytes);
                    break;
                default:
                    make_pkcs7_padding(data_bytes);
            }
            unsigned long data_size = data_bytes.size();
            unsigned long raw_size = data_bytes.size();
            if (!CryptEncrypt(crypt_key_handle,
                              0,
                              FALSE,
                              0,
                              data_bytes.data(),
                              &data_size,
                              0)) {
                error_code = GetLastError();
                if (error_code == ERROR_MORE_DATA) {
                    data_bytes.resize(data_size);
                    if (!CryptEncrypt(crypt_key_handle,
                                      0,
                                      FALSE,
                                      0,
                                      data_bytes.data(),
                                      &raw_size,
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

    bool aes256::decode_process(std::vector<uint8_t> &data_bytes,
                                AesPadding padding) {
        do {
            unsigned long data_size = data_bytes.size();
            if (!CryptDecrypt(crypt_key_handle,
                              0,
                              FALSE,
                              0,
                              data_bytes.data(),
                              &data_size)) {
                error_code = GetLastError();
                break;
            }
            bool is_false = false;
            switch (padding) {
                case AesPadding::PKCS7_PADDING:
                    if (!remove_pkcs7_padding(data_bytes, data_size)) {
                        is_false = true;
                    }
                    break;
                case AesPadding::ISO10126_PADDING:
                    if (!remove_iso10126_padding(data_bytes, data_size)) {
                        is_false = true;
                    }
                    break;
                case AesPadding::ANSI_X923_PADDING:
                    if (!remove_ansix923_padding(data_bytes, data_size)) {
                        is_false = true;
                    }
                    break;
                default:
                    if (!remove_pkcs7_padding(data_bytes, data_size)) {
                        is_false = true;
                    }
            }
            if (is_false) {
                break;
            }
            cleanup();
            return true;
        } while (false);
        cleanup();
        return false;
    }

    std::vector<uint8_t> aes256::encode_cbc(const std::vector<uint8_t> &data,
                                            const std::vector<uint8_t> &key,
                                            const std::vector<uint8_t> &iv,
                                            AesPadding padding) {
        if (data.empty() ||
            key.empty() ||
            iv.empty() ||
            key.size() != 32 ||
            iv.size() != 16) {
            return {};
        }
        do {
            data_bytes.resize(data.size());
            memcpy(data_bytes.data(), data.data(), data.size());
            std::vector<uint8_t> key_bytes(key.begin(), key.end());
            std::vector<uint8_t> local_iv(iv.begin(), iv.end());
            if (!pre_process(key_bytes, local_iv, AesMode::MODE_CBC)) {
                break;
            }
            if (!encode_process(data_bytes, padding)) {
                break;
            }
            is_done = true;
            return data_bytes;
        } while (false);
        return {};
    }

    std::vector<uint8_t> aes256::decode_cbc(const std::vector<uint8_t> &data,
                                            const std::vector<uint8_t> &key,
                                            const std::vector<uint8_t> &iv,
                                            AesPadding padding) {
        if (data.empty() ||
            key.empty() ||
            iv.empty() ||
            key.size() != 32 ||
            iv.size() != 16) {
            return {};
        }
        do {
            data_bytes.resize(data.size());
            memcpy(data_bytes.data(), data.data(), data.size());
            std::vector<uint8_t> key_bytes(key.begin(), key.end());
            std::vector<uint8_t> local_iv(iv.begin(), iv.end());
            if (!pre_process(key_bytes, local_iv, AesMode::MODE_CBC)) {
                break;
            }
            if (!decode_process(data_bytes, padding)) {
                break;
            }
            is_done = true;
            return data_bytes;
        } while (false);
        return {};
    }

    std::vector<uint8_t> aes256::encode_ecb(const std::vector<uint8_t> &data,
                                            const std::vector<uint8_t> &key,
                                            AesPadding padding) {
        if (data.empty() ||
            key.empty() ||
            key.size() != 32) {
            return {};
        }
        do {
            data_bytes.resize(data.size());
            memcpy(data_bytes.data(), data.data(), data.size());
            std::vector<uint8_t> key_bytes(key.begin(), key.end());
            std::vector<uint8_t> iv;
            if (!pre_process(key_bytes, iv, AesMode::MODE_ECB)) {
                break;
            }
            if (!encode_process(data_bytes, padding)) {
                break;
            }
            is_done = true;
            return data_bytes;
        } while (false);
        return {};
    }

    std::vector<uint8_t> aes256::decode_ecb(const std::vector<uint8_t> &data,
                                            const std::vector<uint8_t> &key,
                                            AesPadding padding) {
        if (data.empty() ||
            key.empty() ||
            key.size() != 32) {
            return {};
        }
        do {
            data_bytes.resize(data.size());
            memcpy(data_bytes.data(), data.data(), data.size());
            std::vector<uint8_t> key_bytes(key.begin(), key.end());
            std::vector<uint8_t> iv;
            if (!pre_process(key_bytes, iv, AesMode::MODE_ECB)) {
                break;
            }
            if (!decode_process(data_bytes, padding)) {
                break;
            }
            is_done = true;
            return data_bytes;
        } while (false);
        return {};
    }

    std::vector<uint8_t> aes256::encode_cfb(const std::vector<uint8_t> &data,
                                            const std::vector<uint8_t> &key,
                                            const std::vector<uint8_t> &iv,
                                            AesPadding padding) {
        if (data.empty() ||
            key.empty() ||
            iv.empty() ||
            key.size() != 32 ||
            iv.size() != 16) {
            return {};
        }
        do {
            data_bytes.resize(data.size());
            memcpy(data_bytes.data(), data.data(), data.size());
            std::vector<uint8_t> key_bytes(key.begin(), key.end());
            std::vector<uint8_t> local_iv(iv.begin(), iv.end());
            if (!pre_process(key_bytes, local_iv, AesMode::MODE_CFB)) {
                break;
            }
            if (!encode_process(data_bytes, padding)) {
                break;
            }
            is_done = true;
            return data_bytes;
        } while (false);
        return {};
    }

    std::vector<uint8_t> aes256::decode_cfb(const std::vector<uint8_t> &data,
                                            const std::vector<uint8_t> &key,
                                            const std::vector<uint8_t> &iv,
                                            AesPadding padding) {
        if (data.empty() ||
            key.empty() ||
            iv.empty() ||
            key.size() != 32 ||
            iv.size() != 16) {
            return {};
        }
        do {
            data_bytes.resize(data.size());
            memcpy(data_bytes.data(), data.data(), data.size());
            std::vector<uint8_t> key_bytes(key.begin(), key.end());
            std::vector<uint8_t> local_iv(iv.begin(), iv.end());
            if (!pre_process(key_bytes, local_iv, AesMode::MODE_CFB)) {
                break;
            }
            if (!decode_process(data_bytes, padding)) {
                break;
            }
            is_done = true;
            return data_bytes;
        } while (false);
        return {};
    }

    std::vector<uint8_t> aes256::generate_iv_bytes() {
        do {
            wchar_t provider[] =
                    L"Microsoft Enhanced RSA and AES Cryptographic Provider";
            if (!CryptAcquireContextW(&crypt_prov_handle,
                                      nullptr,
                                      provider,
                                      PROV_RSA_AES,
                                      CRYPT_VERIFYCONTEXT)) {
                error_code = GetLastError();
                break;
            }
            std::vector<uint8_t> iv(16, 0);
            if (!CryptGenRandom(crypt_prov_handle, iv.size(), iv.data())) {
                break;
            }
            cleanup();
            return iv;
        } while (false);
        cleanup();
        return {};
    }

    std::string aes256::generate_iv_string() {
        std::vector<uint8_t> iv = generate_iv_bytes();
        std::string result(iv.begin(), iv.end());
        return result;
    }

    std::string aes256::hex_string() const {
        if (is_done) {
            return format_hex_fast(data_bytes);
        }
        return {};
    }

    unsigned long aes256::err_code() const {
        return error_code;
    }

    std::string aes256::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring aes256::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
