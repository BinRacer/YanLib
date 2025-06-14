/* clang-format off */
/*
 * @file md5.cpp
 * @date 2025-04-07
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
#include "md5.h"

namespace YanLib::hash {
    md5::md5(const std::vector<uint8_t> &data) {
        crypt_prov_handle = 0;
        crypt_hash_handle = 0;
        data_bytes = data;
        hash_bytes = {};
        file_name = {};
        is_file = false;
        error_code = 0;
    }

    md5::md5(const std::string &data) {
        crypt_prov_handle = 0;
        crypt_hash_handle = 0;
        data_bytes.resize(data.size());
        memcpy(data_bytes.data(), data.data(), data.size());
        hash_bytes = {};
        file_name = {};
        is_file = false;
        error_code = 0;
    }

    md5::md5(const char *filename, helper::CodePage code_page) {
        crypt_prov_handle = 0;
        crypt_hash_handle = 0;
        data_bytes = {};
        hash_bytes = {};
        file_name = helper::convert::str_to_wstr(filename, code_page);
        is_file = true;
        error_code = 0;
    }

    md5::md5(const wchar_t *filename) {
        crypt_prov_handle = 0;
        crypt_hash_handle = 0;
        data_bytes = {};
        hash_bytes = {};
        file_name = filename;
        is_file = true;
        error_code = 0;
    }

    md5::~md5() {
        if (crypt_hash_handle) {
            CryptDestroyHash(crypt_hash_handle);
            crypt_hash_handle = 0;
        }
        if (crypt_prov_handle) {
            CryptReleaseContext(crypt_prov_handle, 0);
            crypt_prov_handle = 0;
        }
    }

    std::string md5::format_hex_fast(const std::vector<uint8_t> &data) {
        static constexpr char hex_table[] = "0123456789abcdef";
        std::string hex_str;
        hex_str.reserve(data.size() * 2);
        for (const uint8_t byte : data) {
            hex_str += hex_table[byte >> 4];
            hex_str += hex_table[byte & 0x0F];
        }
        return hex_str;
    }

    bool md5::pre_process() {
        bool result = false;
        do {
            if (!CryptAcquireContextW(&crypt_prov_handle, nullptr, nullptr,
                                      PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
                error_code = GetLastError();
                break;
            }
            if (!CryptCreateHash(crypt_prov_handle, CALG_MD5, 0, 0,
                                 &crypt_hash_handle)) {
                error_code = GetLastError();
                break;
            }
            result = true;
        } while (false);
        return result;
    }

    bool md5::process_file() {
        bool result = false;
        auto file_handle = INVALID_HANDLE_VALUE;
        do {
            file_handle =
                    CreateFileW(file_name.data(), GENERIC_READ | GENERIC_WRITE,
                                FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (file_handle == INVALID_HANDLE_VALUE) {
                error_code = GetLastError();
                break;
            }
            LARGE_INTEGER file_size{};
            if (!GetFileSizeEx(file_handle, &file_size)) {
                error_code = GetLastError();
                break;
            }
            bool is_error = false;
            const size_t total_size = file_size.QuadPart;
            size_t offset = 0;
            while (offset < total_size) {
                const size_t block_size = (total_size - offset) > 4096
                        ? 4096
                        : total_size - offset;
                std::vector<uint8_t> data(block_size, '\0');
                unsigned long bytes_read = 0;
                if (!ReadFile(file_handle, data.data(), data.size(),
                              &bytes_read, nullptr)) {
                    error_code = GetLastError();
                    break;
                }
                if (!CryptHashData(crypt_hash_handle, data.data(), bytes_read,
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
            result = true;
        } while (false);
        if (file_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(file_handle);
        }
        return result;
    }

    bool md5::process_data() {
        bool result = false;
        do {
            bool is_error = false;
            const size_t total_size = data_bytes.size();
            size_t offset = 0;
            while (offset < total_size) {
                const size_t block_size = (total_size - offset) > 4096
                        ? 4096
                        : total_size - offset;
                if (const uint8_t *block_ptr = data_bytes.data() + offset;
                    !CryptHashData(crypt_hash_handle, block_ptr,
                                   static_cast<uint32_t>(block_size), 0)) {
                    error_code = GetLastError();
                    is_error = true;
                    break;
                }
                offset += block_size;
            }
            if (is_error) {
                break;
            }
            result = true;
        } while (false);
        return result;
    }

    std::vector<uint8_t> md5::process() {
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
        } while (false);
        return hash_bytes;
    }

    bool md5::post_process() {
        bool result = false;
        do {
            unsigned long len = 0;
            unsigned long data_len = sizeof(uint32_t);
            if (!CryptGetHashParam(crypt_hash_handle, HP_HASHSIZE,
                                   reinterpret_cast<uint8_t *>(&len), &data_len,
                                   0)) {
                error_code = GetLastError();
                break;
            }
            hash_bytes.resize(len);
            if (!CryptGetHashParam(crypt_hash_handle, HP_HASHVAL,
                                   hash_bytes.data(), &len, 0)) {
                error_code = GetLastError();
                break;
            }
            result = true;
        } while (false);
        return result;
    }

    std::vector<uint8_t> md5::hash() {
        if (is_done) {
            return hash_bytes;
        }
        return process();
    }

    std::string md5::hash_string() {
        std::string result;
        if (error_code == 0 && hash_bytes.empty()) {
            hash_bytes = process();
            return format_hex_fast(hash_bytes);
        }
        return format_hex_fast(hash_bytes);
    }

    std::wstring md5::hash_wstring(helper::CodePage code_page) {
        return helper::convert::str_to_wstr(hash_string(), code_page);
    }

    uint32_t md5::err_code() const {
        return error_code;
    }

    std::string md5::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring md5::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::hash
