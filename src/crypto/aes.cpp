/* clang-format off */
/*
 * @file aes.cpp
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
#include "aes.h"
#include "helper/convert.h"
#include <random>

namespace YanLib::crypto {
    aes::aes() {
        crypt_prov_handle = 0;
        crypt_hash_handle = 0;
        crypt_key_handle = 0;
        data_bytes = {};
        error_code = 0;
    }

    aes::~aes() {
        cleanup();
    }

    void aes::cleanup() {
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

    std::string aes::format_hex_fast(const std::vector<uint8_t> &data) {
        static constexpr char hex_table[] = "0123456789abcdef";
        std::string hex_str;
        hex_str.reserve(data.size() * 2);
        for (const uint8_t byte : data) {
            hex_str += hex_table[byte >> 4];
            hex_str += hex_table[byte & 0x0F];
        }
        return hex_str;
    }

    aes::KeyBlob aes::make_blob(const std::vector<uint8_t> &key) {
        KeyBlob blob{};
        blob.header = {PLAINTEXTKEYBLOB, CUR_BLOB_VERSION, 0, CALG_AES_128};
        blob.key_size = 16;
        memcpy(blob.key, key.data(), key.size());
        return blob;
    }

    void aes::make_pkcs7_padding(std::vector<uint8_t> &data) {
        const size_t raw_size = data.size();
        const size_t pad_len = 16 - (raw_size % 16);
        if (pad_len == 0) {
            return;
        }
        data.insert(data.end(), pad_len, static_cast<uint8_t>(pad_len));
    }

    bool aes::remove_pkcs7_padding(std::vector<uint8_t> &data,
                                   const uint32_t real_size) {
        bool result = false;
        do {
            if (data.empty() || real_size < 1 || real_size > data.size()) {
                break;
            }
            const uint8_t pad_len = data[real_size - 1];
            if (pad_len < 1 || pad_len > 16) {
                break;
            }
            for (uint32_t i = real_size - pad_len; i < real_size; i++) {
                if (data[i] != pad_len) {
                    return false;
                }
            }
            data.resize(real_size - pad_len);
            result = true;
        } while (false);
        return result;
    }

    void aes::make_iso10126_padding(std::vector<uint8_t> &data) {
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

    bool aes::remove_iso10126_padding(std::vector<uint8_t> &data,
                                      const uint32_t real_size) {
        bool result = false;
        do {
            if (data.empty() || real_size < 1 || real_size > data.size()) {
                break;
            }
            const uint8_t pad_len = data[real_size - 1];
            if (pad_len < 1 || pad_len > 16) {
                break;
            }
            data.resize(real_size - pad_len);
            result = true;
        } while (false);
        return result;
    }

    void aes::make_ansix923_padding(std::vector<uint8_t> &data) {
        const size_t raw_size = data.size();
        const size_t pad_len = 16 - (raw_size % 16);
        if (pad_len == 0) {
            return;
        }
        data.insert(data.end(), pad_len - 1, 0);
        data.push_back(static_cast<uint8_t>(pad_len));
    }

    bool aes::remove_ansix923_padding(std::vector<uint8_t> &data,
                                      const uint32_t real_size) {
        bool result = false;
        do {
            if (data.empty() || real_size < 1 || real_size > data.size()) {
                break;
            }
            const uint8_t pad_len = data[real_size - 1];
            if (pad_len < 1 || pad_len > 16) {
                break;
            }
            for (uint32_t i = real_size - pad_len; i < real_size - 1; i++) {
                if (data[i] != 0) {
                    return false;
                }
            }
            data.resize(real_size - pad_len);
            result = true;
        } while (false);
        return result;
    }

    bool aes::pre_process(const std::vector<uint8_t> &key_bytes,
                          const std::vector<uint8_t> &iv,
                          AesMode mode) {
        bool result = false;
        do {
            constexpr wchar_t provider[] =
                    L"Microsoft Enhanced RSA and AES Cryptographic Provider";
            if (!CryptAcquireContextW(&crypt_prov_handle, nullptr, provider,
                                      PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
                error_code = GetLastError();
                break;
            }

            KeyBlob blob = make_blob(key_bytes);
            if (!CryptImportKey(crypt_prov_handle,
                                reinterpret_cast<uint8_t *>(&blob),
                                sizeof(blob), 0, 0, &crypt_key_handle)) {
                error_code = GetLastError();
                break;
            }
            auto aes_mode = static_cast<uint32_t>(mode);
            if (!CryptSetKeyParam(crypt_key_handle, KP_MODE,
                                  reinterpret_cast<uint8_t *>(&aes_mode), 0)) {
                error_code = GetLastError();
                break;
            }
            if (mode != AesMode::ECB) {
                uint8_t local_iv[16];
                memcpy(local_iv, iv.data(), 16);
                if (!CryptSetKeyParam(crypt_key_handle, KP_IV, local_iv, 0)) {
                    error_code = GetLastError();
                    break;
                }
            }
            result = true;
        } while (false);
        return result;
    }

    bool aes::encode_process(std::vector<uint8_t> &data_bytes,
                             const AesPadding padding) {
        bool result = false;
        do {
            switch (padding) {
                case AesPadding::PKCS7:
                    make_pkcs7_padding(data_bytes);
                    break;
                case AesPadding::ISO10126:
                    make_iso10126_padding(data_bytes);
                    break;
                case AesPadding::ANSIX923:
                    make_ansix923_padding(data_bytes);
                    break;
                default:
                    make_pkcs7_padding(data_bytes);
            }
            unsigned long data_size = data_bytes.size();
            unsigned long raw_size = data_bytes.size();
            if (!CryptEncrypt(crypt_key_handle, 0, FALSE, 0, data_bytes.data(),
                              &data_size, 0)) {
                error_code = GetLastError();
                if (error_code == ERROR_MORE_DATA) {
                    data_bytes.resize(data_size);
                    if (!CryptEncrypt(crypt_key_handle, 0, FALSE, 0,
                                      data_bytes.data(), &raw_size,
                                      data_bytes.size())) {
                        error_code = GetLastError();
                        break;
                    }
                } else {
                    break;
                }
            }
            result = true;
        } while (false);
        cleanup();
        return result;
    }

    bool aes::decode_process(std::vector<uint8_t> &data_bytes,
                             const AesPadding padding) {
        bool result = false;
        do {
            unsigned long data_size = data_bytes.size();
            if (!CryptDecrypt(crypt_key_handle, 0, FALSE, 0, data_bytes.data(),
                              &data_size)) {
                error_code = GetLastError();
                break;
            }
            bool is_false = false;
            switch (padding) {
                case AesPadding::PKCS7:
                    if (!remove_pkcs7_padding(data_bytes, data_size)) {
                        is_false = true;
                    }
                    break;
                case AesPadding::ISO10126:
                    if (!remove_iso10126_padding(data_bytes, data_size)) {
                        is_false = true;
                    }
                    break;
                case AesPadding::ANSIX923:
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
            result = true;
        } while (false);
        cleanup();
        return result;
    }

    std::vector<uint8_t> aes::encode_cbc(const std::vector<uint8_t> &data,
                                         const std::vector<uint8_t> &key,
                                         const std::vector<uint8_t> &iv,
                                         const AesPadding padding) {
        if (data.empty() || key.empty() || iv.empty() || key.size() != 16 ||
            iv.size() != 16) {
            return {};
        }
        data_bytes.resize(data.size());
        memcpy(data_bytes.data(), data.data(), data.size());
        const std::vector key_bytes(key.begin(), key.end());
        if (const std::vector localIV(iv.begin(), iv.end());
            !pre_process(key_bytes, localIV, AesMode::CBC)) {
            return {};
        }
        if (!encode_process(data_bytes, padding)) {
            return {};
        }
        is_done = true;
        return data_bytes;
    }

    std::vector<uint8_t> aes::decode_cbc(const std::vector<uint8_t> &data,
                                         const std::vector<uint8_t> &key,
                                         const std::vector<uint8_t> &iv,
                                         const AesPadding padding) {
        if (data.empty() || key.empty() || iv.empty() || key.size() != 16 ||
            iv.size() != 16) {
            return {};
        }
        data_bytes.resize(data.size());
        memcpy(data_bytes.data(), data.data(), data.size());
        const std::vector key_bytes(key.begin(), key.end());
        if (const std::vector local_iv(iv.begin(), iv.end());
            !pre_process(key_bytes, local_iv, AesMode::CBC)) {
            return {};
        }
        if (!decode_process(data_bytes, padding)) {
            return {};
        }
        is_done = true;
        return data_bytes;
    }

    std::vector<uint8_t> aes::encode_ecb(const std::vector<uint8_t> &data,
                                         const std::vector<uint8_t> &key,
                                         const AesPadding padding) {
        if (data.empty() || key.empty() || key.size() != 16) {
            return {};
        }
        data_bytes.resize(data.size());
        memcpy(data_bytes.data(), data.data(), data.size());
        const std::vector key_bytes(key.begin(), key.end());
        if (const std::vector<uint8_t> iv(16, '\0');
            !pre_process(key_bytes, iv, AesMode::ECB)) {
            return {};
        }
        if (!encode_process(data_bytes, padding)) {
            return {};
        }
        is_done = true;
        return data_bytes;
    }

    std::vector<uint8_t> aes::decode_ecb(const std::vector<uint8_t> &data,
                                         const std::vector<uint8_t> &key,
                                         const AesPadding padding) {
        if (data.empty() || key.empty() || key.size() != 16) {
            return {};
        }
        data_bytes.resize(data.size());
        memcpy(data_bytes.data(), data.data(), data.size());
        const std::vector key_bytes(key.begin(), key.end());
        if (const std::vector<uint8_t> iv(16, '\0');
            !pre_process(key_bytes, iv, AesMode::ECB)) {
            return {};
        }
        if (!decode_process(data_bytes, padding)) {
            return {};
        }
        is_done = true;
        return data_bytes;
    }

    std::vector<uint8_t> aes::encode_cfb(const std::vector<uint8_t> &data,
                                         const std::vector<uint8_t> &key,
                                         const std::vector<uint8_t> &iv,
                                         const AesPadding padding) {
        if (data.empty() || key.empty() || iv.empty() || key.size() != 16 ||
            iv.size() != 16) {
            return {};
        }
        data_bytes.resize(data.size());
        memcpy(data_bytes.data(), data.data(), data.size());
        const std::vector key_bytes(key.begin(), key.end());
        if (const std::vector local_iv(iv.begin(), iv.end());
            !pre_process(key_bytes, local_iv, AesMode::CFB)) {
            return {};
        }
        if (!encode_process(data_bytes, padding)) {
            return {};
        }
        is_done = true;
        return data_bytes;
    }

    std::vector<uint8_t> aes::decode_cfb(const std::vector<uint8_t> &data,
                                         const std::vector<uint8_t> &key,
                                         const std::vector<uint8_t> &iv,
                                         const AesPadding padding) {
        if (data.empty() || key.empty() || iv.empty() || key.size() != 16 ||
            iv.size() != 16) {
            return {};
        }
        data_bytes.resize(data.size());
        memcpy(data_bytes.data(), data.data(), data.size());
        const std::vector key_bytes(key.begin(), key.end());
        if (const std::vector local_iv(iv.begin(), iv.end());
            !pre_process(key_bytes, local_iv, AesMode::CFB)) {
            return {};
        }
        if (!decode_process(data_bytes, padding)) {
            return {};
        }
        is_done = true;
        return data_bytes;
    }

    std::vector<uint8_t> aes::generate_iv_bytes() {
        std::vector<uint8_t> iv = {};
        do {
            constexpr wchar_t provider[] =
                    L"Microsoft Enhanced RSA and AES Cryptographic Provider";
            if (!CryptAcquireContextW(&crypt_prov_handle, nullptr, provider,
                                      PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
                error_code = GetLastError();
                break;
            }
            iv.resize(16);
            if (!CryptGenRandom(crypt_prov_handle, iv.size(), iv.data())) {
                break;
            }
        } while (false);
        cleanup();
        return iv;
    }

    std::string aes::generate_iv_string() {
        std::vector<uint8_t> iv = generate_iv_bytes();
        std::string result(iv.begin(), iv.end());
        return result;
    }

    std::string aes::hex_string() const {
        if (is_done) {
            return format_hex_fast(data_bytes);
        }
        return {};
    }

    uint32_t aes::err_code() const {
        return error_code;
    }

    std::string aes::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring aes::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::crypto
