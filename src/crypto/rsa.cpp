//
// Created by forkernel on 2025/4/12.
//

#include "rsa.h"
#include "base64.h"
#include "../helper/convert.h"
#pragma comment(lib, "crypt32.lib")

namespace YanLib::crypto {
    void rsa::cleanup() {
        if (hCryptKey) {
            CryptDestroyKey(hCryptKey);
            hCryptKey = 0;
        }
        if (hCryptProv) {
            CryptReleaseContext(hCryptProv, 0);
            hCryptProv = 0;
        }
    }

    rsa::~rsa() {
        cleanup();
    }

    std::string rsa::format_hex_fast(const std::vector<uint8_t> &data) {
        static constexpr char hexTable[] = "0123456789abcdef";
        std::string hexStr;
        hexStr.reserve(data.size() * 2);
        for (uint8_t byte: data) {
            hexStr += hexTable[byte >> 4];
            hexStr += hexTable[byte & 0x0F];
        }
        return hexStr;
    }

    bool rsa::generate_key(RSA_KEY_LENGTH key_length) {
        do {
            wchar_t provider[] =
                    L"Microsoft Enhanced RSA and AES Cryptographic Provider";
            if (!CryptAcquireContextW(&hCryptProv,
                                      nullptr,
                                      provider,
                                      PROV_RSA_AES,
                                      0)) {
                error_code = GetLastError();
                break;
            }
            if (!CryptGenKey(hCryptProv,
                             AT_KEYEXCHANGE,
                             CRYPT_EXPORTABLE | key_length,
                             &hCryptKey)) {
                error_code = GetLastError();
                break;
            }
            DWORD publen = 0;
            if (!CryptExportKey(hCryptKey,
                                0,
                                PUBLICKEYBLOB,
                                0,
                                nullptr,
                                &publen)) {
                error_code = GetLastError();
                break;
            }
            pub_key.resize(publen);
            if (!CryptExportKey(hCryptKey,
                                0,
                                PUBLICKEYBLOB,
                                0,
                                pub_key.data(),
                                &publen)) {
                error_code = GetLastError();
                break;
            }
            DWORD privlen = 0;
            if (!CryptExportKey(hCryptKey,
                                0,
                                PRIVATEKEYBLOB,
                                0,
                                nullptr,
                                &privlen)) {
                error_code = GetLastError();
                break;
            }
            priv_key.resize(privlen);
            if (!CryptExportKey(hCryptKey,
                                0,
                                PRIVATEKEYBLOB,
                                0,
                                priv_key.data(),
                                &privlen)) {
                error_code = GetLastError();
                break;
            }
            cleanup();
            return true;
        } while (false);
        cleanup();
        return false;
    }


    std::vector<uint8_t> rsa::encode(const std::vector<uint8_t> &data,
                                     const std::vector<uint8_t> &pub_blob) {
        do {
            wchar_t provider[] =
                    L"Microsoft Enhanced RSA and AES Cryptographic Provider";
            if (!CryptAcquireContextW(&hCryptProv,
                                      nullptr,
                                      provider,
                                      PROV_RSA_AES,
                                      0)) {
                error_code = GetLastError();
                break;
            }
            if (!CryptImportKey(hCryptProv, pub_blob.data(),
                                pub_blob.size(),
                                0,
                                0,
                                &hCryptKey)) {
                error_code = GetLastError();
                break;
            }
            std::vector<uint8_t> encode_data(data.begin(), data.end());
            DWORD dataSize = data.size();
            DWORD rawSize = data.size();
            if (!CryptEncrypt(hCryptKey,
                              0,
                              TRUE,
                              0,
                              encode_data.data(),
                              &dataSize,
                              0)) {
                error_code = GetLastError();
                if (error_code == ERROR_MORE_DATA) {
                    encode_data.resize(dataSize);
                    if (!CryptEncrypt(hCryptKey,
                                      0,
                                      TRUE,
                                      0,
                                      encode_data.data(),
                                      &rawSize,
                                      encode_data.size())) {
                        error_code = GetLastError();
                        break;
                    }
                } else {
                    break;
                }
            }
            cleanup();
            return encode_data;
        } while (false);
        cleanup();
        return {};
    }

    std::vector<uint8_t> rsa::decode(const std::vector<uint8_t> &data,
                                     const std::vector<uint8_t> &priv_blob) {
        do {
            wchar_t provider[] =
                    L"Microsoft Enhanced RSA and AES Cryptographic Provider";
            if (!CryptAcquireContextW(&hCryptProv,
                                      nullptr,
                                      provider,
                                      PROV_RSA_AES,
                                      0)) {
                error_code = GetLastError();
                break;
            }
            if (!CryptImportKey(hCryptProv, priv_blob.data(),
                                priv_blob.size(),
                                0,
                                0,
                                &hCryptKey)) {
                error_code = GetLastError();
                break;
            }
            std::vector<uint8_t> decode_data(data.begin(), data.end());
            DWORD dataSize = data.size();
            if (!CryptDecrypt(hCryptKey,
                              0,
                              TRUE,
                              0,
                              decode_data.data(),
                              &dataSize)) {
                error_code = GetLastError();
                break;
            }
            decode_data.resize(dataSize);
            cleanup();
            return decode_data;
        } while (false);
        cleanup();
        return {};
    }

    std::string rsa::encode_to_base64(const std::vector<uint8_t> &data,
                                      const std::vector<uint8_t> &pub_blob) {
        std::vector<uint8_t> encoded = encode(data, pub_blob);
        std::vector<uint8_t> base64_encoded = base64::encode(encoded.data(),
                                                             encoded.size());
        std::string result(base64_encoded.begin(), base64_encoded.end());
        return result;
    }

    std::string rsa::decode_to_base64(const std::vector<uint8_t> &data,
                                      const std::vector<uint8_t> &priv_blob) {
        std::vector<uint8_t> decoded = encode(data, priv_blob);
        std::vector<uint8_t> base64_encoded = base64::decode(decoded.data(),
                                                             decoded.size());
        std::string result(base64_encoded.begin(), base64_encoded.end());
        return result;
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
        std::vector<uint8_t> base64_encoded = base64::encode(pub_key.data(),
                                                             pub_key.size());
        std::string result(base64_encoded.begin(), base64_encoded.end());
        return result;
    }

    std::string rsa::priv_base64() const {
        std::vector<uint8_t> base64_encoded = base64::encode(priv_key.data(),
                                                             priv_key.size());
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
            size_t chunk_size = ((base64_pubkey.size() - pos) > 64)
                                    ? 64
                                    : base64_pubkey.size() - pos;
            pubkey.append(
                reinterpret_cast<char *>(&base64_pubkey[pos]), chunk_size);
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
        std::vector<uint8_t> base64_privkey = base64::encode(priv_key.data(),
                                                             priv_key.size());
        std::string privkey;
        privkey.reserve(base64_privkey.size() + 64);

        privkey.append("-----BEGIN PRIVATE KEY-----\n");
        size_t pos = 0;
        while (pos < base64_privkey.size()) {
            size_t chunk_size = ((base64_privkey.size() - pos) > 64)
                                    ? 64
                                    : base64_privkey.size() - pos;
            privkey.append(
                reinterpret_cast<char *>(&base64_privkey[pos]), chunk_size);
            privkey.push_back('\n');
            pos += chunk_size;
        }

        if (!privkey.empty() && privkey.back() == '\n') {
            privkey.pop_back();
        }
        privkey.append("\n-----END PRIVATE KEY-----");
        return privkey;
    }

    DWORD rsa::err_code() const {
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
}
