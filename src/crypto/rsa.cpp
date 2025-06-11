/* clang-format off */
/*
 * @file rsa.cpp
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
#include "rsa.h"
#include "base64.h"
#include "helper/convert.h"

namespace YanLib::crypto {
    void rsa::cleanup() {
        if (crypt_key_handle) {
            CryptDestroyKey(crypt_key_handle);
            crypt_key_handle = 0;
        }
        if (crypt_prov_handle) {
            CryptReleaseContext(crypt_prov_handle, 0);
            crypt_prov_handle = 0;
        }
    }

    rsa::~rsa() {
        cleanup();
    }

    std::string rsa::format_hex_fast(const std::vector<uint8_t> &data) {
        static constexpr char hex_table[] = "0123456789abcdef";
        std::string hex_str;
        hex_str.reserve(data.size() * 2);
        for (const uint8_t byte : data) {
            hex_str += hex_table[byte >> 4];
            hex_str += hex_table[byte & 0x0F];
        }
        return hex_str;
    }

    bool rsa::generate_key(RsaKeyBits key_bits) {
        bool result = false;
        do {
            constexpr wchar_t provider[] =
                    L"Microsoft Enhanced RSA and AES Cryptographic Provider";
            if (!CryptAcquireContextW(&crypt_prov_handle, nullptr, provider,
                                      PROV_RSA_AES, 0)) {
                error_code = GetLastError();
                break;
            }
            if (!CryptGenKey(crypt_prov_handle, AT_KEYEXCHANGE,
                             CRYPT_EXPORTABLE | static_cast<uint32_t>(key_bits),
                             &crypt_key_handle)) {
                error_code = GetLastError();
                break;
            }
            unsigned long publen = 0;
            if (!CryptExportKey(crypt_key_handle, 0, PUBLICKEYBLOB, 0, nullptr,
                                &publen)) {
                error_code = GetLastError();
                break;
            }
            pub_key.resize(publen);
            if (!CryptExportKey(crypt_key_handle, 0, PUBLICKEYBLOB, 0,
                                pub_key.data(), &publen)) {
                error_code = GetLastError();
                break;
            }
            unsigned long privlen = 0;
            if (!CryptExportKey(crypt_key_handle, 0, PRIVATEKEYBLOB, 0, nullptr,
                                &privlen)) {
                error_code = GetLastError();
                break;
            }
            priv_key.resize(privlen);
            if (!CryptExportKey(crypt_key_handle, 0, PRIVATEKEYBLOB, 0,
                                priv_key.data(), &privlen)) {
                error_code = GetLastError();
                break;
            }
            result = true;
        } while (false);
        cleanup();
        return result;
    }

    std::vector<uint8_t> rsa::encode(const std::vector<uint8_t> &data,
                                     const std::vector<uint8_t> &pub_blob) {
        std::vector<uint8_t> encode_data = {};
        do {
            constexpr wchar_t provider[] =
                    L"Microsoft Enhanced RSA and AES Cryptographic Provider";
            if (!CryptAcquireContextW(&crypt_prov_handle, nullptr, provider,
                                      PROV_RSA_AES, 0)) {
                error_code = GetLastError();
                break;
            }
            if (!CryptImportKey(crypt_prov_handle, pub_blob.data(),
                                pub_blob.size(), 0, 0, &crypt_key_handle)) {
                error_code = GetLastError();
                break;
            }
            encode_data.insert(encode_data.begin(), data.begin(), data.end());
            unsigned long data_size = data.size();
            unsigned long raw_size = data.size();
            if (!CryptEncrypt(crypt_key_handle, 0, TRUE, 0, encode_data.data(),
                              &data_size, 0)) {
                error_code = GetLastError();
                if (error_code == ERROR_MORE_DATA) {
                    encode_data.resize(data_size);
                    if (!CryptEncrypt(crypt_key_handle, 0, TRUE, 0,
                                      encode_data.data(), &raw_size,
                                      encode_data.size())) {
                        error_code = GetLastError();
                        break;
                    }
                } else {
                    break;
                }
            }
        } while (false);
        cleanup();
        return encode_data;
    }

    std::vector<uint8_t> rsa::decode(const std::vector<uint8_t> &data,
                                     const std::vector<uint8_t> &priv_blob) {
        std::vector<uint8_t> decode_data = {};
        do {
            constexpr wchar_t provider[] =
                    L"Microsoft Enhanced RSA and AES Cryptographic Provider";
            if (!CryptAcquireContextW(&crypt_prov_handle, nullptr, provider,
                                      PROV_RSA_AES, 0)) {
                error_code = GetLastError();
                break;
            }
            if (!CryptImportKey(crypt_prov_handle, priv_blob.data(),
                                priv_blob.size(), 0, 0, &crypt_key_handle)) {
                error_code = GetLastError();
                break;
            }
            decode_data.insert(decode_data.begin(), data.begin(), data.end());
            unsigned long data_size = data.size();
            if (!CryptDecrypt(crypt_key_handle, 0, TRUE, 0, decode_data.data(),
                              &data_size)) {
                error_code = GetLastError();
                break;
            }
            decode_data.resize(data_size);
        } while (false);
        cleanup();
        return decode_data;
    }

    std::vector<uint8_t>
    rsa::encode_to_base64(const std::vector<uint8_t> &data,
                          const std::vector<uint8_t> &pub_blob) {
        return base64::encode(encode(data, pub_blob));
    }

    std::vector<uint8_t>
    rsa::decode_from_base64(const std::vector<uint8_t> &data,
                            const std::vector<uint8_t> &priv_blob) {
        return decode(base64::decode(data), priv_blob);
    }

    std::vector<uint8_t> rsa::pub_blob() const {
        return pub_key;
    }

    std::vector<uint8_t> rsa::priv_blob() const {
        return priv_key;
    }

    std::string rsa::pub_hex() const {
        return format_hex_fast(pub_key);
    }

    std::string rsa::priv_hex() const {
        return format_hex_fast(priv_key);
    }

    std::string rsa::pub_base64() const {
        std::vector<uint8_t> base64_encoded =
                base64::encode(pub_key.data(), pub_key.size());
        std::string result(base64_encoded.begin(), base64_encoded.end());
        return result;
    }

    std::string rsa::priv_base64() const {
        std::vector<uint8_t> base64_encoded =
                base64::encode(priv_key.data(), priv_key.size());
        std::string result(base64_encoded.begin(), base64_encoded.end());
        return result;
    }

    std::string rsa::pub_pem() const {
        std::vector<uint8_t> base64_pubkey = base64::encode(pub_key);
        std::string pubkey;
        pubkey.reserve(base64_pubkey.size() + 64);

        pubkey.append("-----BEGIN PUBLIC KEY-----\n");
        size_t pos = 0;
        while (pos < base64_pubkey.size()) {
            const size_t chunk_size = ((base64_pubkey.size() - pos) > 64)
                    ? 64
                    : base64_pubkey.size() - pos;
            pubkey.append(reinterpret_cast<char *>(&base64_pubkey[pos]),
                          chunk_size);
            pubkey.push_back('\n');
            pos += chunk_size;
        }

        if (!pubkey.empty() && pubkey.back() == '\n') {
            pubkey.pop_back();
        }
        pubkey.append("\n-----END PUBLIC KEY-----");
        return pubkey;
    }

    std::string rsa::priv_pem() const {
        std::vector<uint8_t> base64_privkey =
                base64::encode(priv_key.data(), priv_key.size());
        std::string privkey;
        privkey.reserve(base64_privkey.size() + 64);

        privkey.append("-----BEGIN PRIVATE KEY-----\n");
        size_t pos = 0;
        while (pos < base64_privkey.size()) {
            const size_t chunk_size = ((base64_privkey.size() - pos) > 64)
                    ? 64
                    : base64_privkey.size() - pos;
            privkey.append(reinterpret_cast<char *>(&base64_privkey[pos]),
                           chunk_size);
            privkey.push_back('\n');
            pos += chunk_size;
        }

        if (!privkey.empty() && privkey.back() == '\n') {
            privkey.pop_back();
        }
        privkey.append("\n-----END PRIVATE KEY-----");
        return privkey;
    }

    uint32_t rsa::err_code() const {
        return error_code;
    }

    std::string rsa::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring rsa::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::crypto
