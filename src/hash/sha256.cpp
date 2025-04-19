//
// Created by forkernel on 2025/4/8.
//

#include "sha256.h"
#include "helper/convert.h"
#include "../io/fs.h"

namespace YanLib::hash {
    sha256::sha256(const std::vector<uint8_t> &data) {
        crypt_prov_handle = 0;
        crypt_hash_handle = 0;
        data_bytes = data;
        hash_bytes = {};
        file_name = {};
        is_file = false;
        error_code = 0;
    }

    sha256::sha256(const std::string &data) {
        crypt_prov_handle = 0;
        crypt_hash_handle = 0;
        data_bytes.resize(data.size());
        memcpy(data_bytes.data(), data.data(), data.size());
        hash_bytes = {};
        file_name = {};
        is_file = false;
        error_code = 0;
    }

    sha256::sha256(const std::wstring &filename) {
        crypt_prov_handle = 0;
        crypt_hash_handle = 0;
        data_bytes = {};
        hash_bytes = {};
        file_name = filename;
        is_file = true;
        error_code = 0;
    }

    sha256::~sha256() {
        if (crypt_hash_handle) {
            CryptDestroyHash(crypt_hash_handle);
            crypt_hash_handle = 0;
        }
        if (crypt_prov_handle) {
            CryptReleaseContext(crypt_prov_handle, 0);
            crypt_prov_handle = 0;
        }
    }

    std::string sha256::format_hex_fast(const std::vector<uint8_t> &data) {
        static constexpr char hex_table[] = "0123456789abcdef";
        std::string hex_str;
        hex_str.reserve(data.size() * 2);
        for (uint8_t byte: data) {
            hex_str += hex_table[byte >> 4];
            hex_str += hex_table[byte & 0x0F];
        }
        return hex_str;
    }

    bool sha256::pre_process() {
        do {
            if (!CryptAcquireContextW(&crypt_prov_handle,
                                      nullptr,
                                      nullptr,
                                      PROV_RSA_AES,
                                      CRYPT_VERIFYCONTEXT)) {
                error_code = GetLastError();
                break;
            }
            if (!CryptCreateHash(crypt_prov_handle,
                                 CALG_SHA_256,
                                 0,
                                 0,
                                 &crypt_hash_handle)) {
                error_code = GetLastError();
                break;
            }
            return true;
        } while (false);
        return false;
    }

    bool sha256::process_file() {
        do {
            io::fs file;
            if (!file.open(file_name.data())) {
                error_code = file.err_code();
                break;
            }
            if (file.size() <= 4096) {
                std::vector<uint8_t> data = file.read_bytes_to_end();
                if (!CryptHashData(crypt_hash_handle,
                                   data.data(),
                                   data.size(),
                                   0)) {
                    error_code = GetLastError();
                    break;
                }
            } else {
                bool is_error = false;
                constexpr size_t BLOCKSIZE = 4096;
                size_t total_size = file.size();
                size_t offset = 0;
                while (offset < total_size) {
                    size_t blockSize = (total_size - offset) > BLOCKSIZE
                                           ? BLOCKSIZE
                                           : total_size - offset;
                    std::vector<uint8_t> data = file.read_bytes(blockSize);
                    if (!CryptHashData(crypt_hash_handle,
                                       data.data(),
                                       data.size(),
                                       0)) {
                        error_code = GetLastError();
                        is_error = true;
                        break;
                    }
                    offset += blockSize;
                }
                if (is_error) {
                    break;
                }
            }
            return true;
        } while (false);
        return false;
    }

    bool sha256::process_data() {
        do {
            if (data_bytes.size() <= 4096) {
                if (!CryptHashData(crypt_hash_handle,
                                   data_bytes.data(),
                                   data_bytes.size(),
                                   0)) {
                    error_code = GetLastError();
                    break;
                }
            } else {
                bool is_error = false;
                constexpr size_t BLOCKSIZE = 4096;
                size_t total_size = data_bytes.size();
                size_t offset = 0;
                while (offset < total_size) {
                    size_t block_size = (total_size - offset) > BLOCKSIZE
                                           ? BLOCKSIZE
                                           : total_size - offset;
                    BYTE *block_ptr = data_bytes.data() + offset;
                    if (!CryptHashData(crypt_hash_handle,
                                       block_ptr,
                                       static_cast<DWORD>(block_size),
                                       0)) {
                        error_code = GetLastError();
                        is_error = true;
                        break;
                    }
                    offset += block_size;
                }
                if (is_error) {
                    break;
                }
            }
            return true;
        } while (false);
        return false;
    }

    std::vector<uint8_t> sha256::process() {
        do {
            if (!pre_process()) {
                break;
            }

            if (is_file) {
                if (!process_file()) {
                    break;
                }
            } else {
                if (!process_data()) {
                    break;
                }
            }

            if (!post_process()) {
                break;
            }
            is_done = true;
            return hash_bytes;
        } while (false);
        return {};
    }

    bool sha256::post_process() {
        do {
            DWORD len = 0;
            DWORD data_len = sizeof(DWORD);
            if (!CryptGetHashParam(crypt_hash_handle,
                                   HP_HASHSIZE,
                                   reinterpret_cast<uint8_t *>(&len),
                                   &data_len,
                                   0)) {
                error_code = GetLastError();
                break;
            }
            hash_bytes.resize(len);
            if (!CryptGetHashParam(crypt_hash_handle,
                                   HP_HASHVAL,
                                   hash_bytes.data(),
                                   &len,
                                   0)) {
                error_code = GetLastError();
                break;
            }
            return true;
        } while (false);
        return false;
    }

    std::vector<uint8_t> sha256::hash() {
        if (is_done) {
            return hash_bytes;
        }
        return process();
    }

    std::string sha256::hash_string() {
        std::string result;
        if (error_code == 0 && hash_bytes.empty()) {
            hash_bytes = process();
            return format_hex_fast(hash_bytes);
        }
        return format_hex_fast(hash_bytes);
    }

    std::wstring sha256::hash_wstring() {
        return helper::convert::str_to_wstr(hash_string());
    }

    DWORD sha256::err_code() const {
        return error_code;
    }

    std::string sha256::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring sha256::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
