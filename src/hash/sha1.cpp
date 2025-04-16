//
// Created by forkernel on 2025/4/8.
//

#include "sha1.h"
#include "helper/convert.h"
#include "../io/fs.h"

namespace YanLib::hash {
    sha1::sha1(const std::vector<uint8_t> &data) {
        hCryptProv = 0;
        hCryptHash = 0;
        data_bytes = data;
        hash_bytes = {};
        file_name = {};
        isFile = false;
        error_code = 0;
    }

    sha1::sha1(const std::string &data) {
        hCryptProv = 0;
        hCryptHash = 0;
        data_bytes.resize(data.size());
        memcpy(data_bytes.data(), data.data(), data.size());
        hash_bytes = {};
        file_name = {};
        isFile = false;
        error_code = 0;
    }

    sha1::sha1(const std::wstring &filename) {
        hCryptProv = 0;
        hCryptHash = 0;
        data_bytes = {};
        hash_bytes = {};
        file_name = filename;
        isFile = true;
        error_code = 0;
    }

    sha1::~sha1() {
        if (hCryptHash) {
            CryptDestroyHash(hCryptHash);
        }
        if (hCryptProv) {
            CryptReleaseContext(hCryptProv, 0);
        }
    }

    std::string sha1::format_hex_fast(const std::vector<uint8_t> &data) {
        static constexpr char hexTable[] = "0123456789abcdef";
        std::string hexStr;
        hexStr.reserve(data.size() * 2);
        for (uint8_t byte: data) {
            hexStr += hexTable[byte >> 4];
            hexStr += hexTable[byte & 0x0F];
        }
        return hexStr;
    }

    bool sha1::pre_process() {
        do {
            if (!CryptAcquireContextW(&hCryptProv,
                                      nullptr,
                                      nullptr,
                                      PROV_RSA_AES,
                                      CRYPT_VERIFYCONTEXT)) {
                error_code = GetLastError();
                break;
            }
            if (!CryptCreateHash(hCryptProv,
                                 CALG_SHA1,
                                 0,
                                 0,
                                 &hCryptHash)) {
                error_code = GetLastError();
                break;
            }
            return true;
        } while (false);
        return false;
    }

    bool sha1::process_file() {
        do {
            io::fs file;
            if (!file.open(file_name.data())) {
                error_code = file.err_code();
                break;
            }
            if (file.size() <= 4096) {
                std::vector<uint8_t> data = file.read_bytes_to_end();
                if (!CryptHashData(hCryptHash,
                                   data.data(),
                                   data.size(),
                                   0)) {
                    error_code = GetLastError();
                    break;
                }
            } else {
                bool isError = false;
                constexpr size_t BLOCK_SIZE = 4096;
                size_t totalSize = file.size();
                size_t offset = 0;
                while (offset < totalSize) {
                    size_t blockSize = (totalSize - offset) > BLOCK_SIZE
                                           ? BLOCK_SIZE
                                           : totalSize - offset;
                    std::vector<uint8_t> data = file.read_bytes(blockSize);
                    if (!CryptHashData(hCryptHash,
                                       data.data(),
                                       data.size(),
                                       0)) {
                        error_code = GetLastError();
                        isError = true;
                        break;
                    }
                    offset += blockSize;
                }
                if (isError) {
                    break;
                }
            }
            return true;
        } while (false);
        return false;
    }

    bool sha1::process_data() {
        do {
            if (data_bytes.size() <= 4096) {
                if (!CryptHashData(hCryptHash,
                                   data_bytes.data(),
                                   data_bytes.size(),
                                   0)) {
                    error_code = GetLastError();
                    break;
                }
            } else {
                bool isError = false;
                constexpr size_t BLOCK_SIZE = 4096;
                size_t totalSize = data_bytes.size();
                size_t offset = 0;
                while (offset < totalSize) {
                    size_t blockSize = (totalSize - offset) > BLOCK_SIZE
                                           ? BLOCK_SIZE
                                           : totalSize - offset;
                    BYTE *blockPtr = data_bytes.data() + offset;
                    if (!CryptHashData(hCryptHash,
                                       blockPtr,
                                       static_cast<DWORD>(blockSize),
                                       0)) {
                        error_code = GetLastError();
                        isError = true;
                        break;
                    }
                    offset += blockSize;
                }
                if (isError) {
                    break;
                }
            }
            return true;
        } while (false);
        return false;
    }

    std::vector<uint8_t> sha1::process() {
        do {
            if (!pre_process()) {
                break;
            }

            if (isFile) {
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
            isDone = true;
            return hash_bytes;
        } while (false);
        return {};
    }

    bool sha1::post_process() {
        do {
            DWORD len = 0;
            DWORD dwDataLen = sizeof(DWORD);
            if (!CryptGetHashParam(hCryptHash,
                                   HP_HASHSIZE,
                                   reinterpret_cast<uint8_t *>(&len),
                                   &dwDataLen,
                                   0)) {
                error_code = GetLastError();
                break;
            }
            hash_bytes.resize(len);
            if (!CryptGetHashParam(hCryptHash,
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

    std::vector<uint8_t> sha1::hash() {
        if (isDone) {
            return hash_bytes;
        }
        return process();
    }

    std::string sha1::hash_string() {
        std::string result;
        if (error_code == 0 && hash_bytes.size() == 0) {
            hash_bytes = process();
            return format_hex_fast(hash_bytes);
        }
        return format_hex_fast(hash_bytes);
    }

    std::wstring sha1::hash_wstring() {
        return helper::convert::str_to_wstr(hash_string());
    }

    DWORD sha1::err_code() const {
        return error_code;
    }

    std::string sha1::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring sha1::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
}
