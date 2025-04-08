//
// Created by forkernel on 2025/4/8.
//

#ifndef SHA256_H
#define SHA256_H
#include <Windows.h>
#include <string>
#include <vector>
namespace YanLib {
    namespace crypto {
        class sha256 {
        public:
            sha256(const sha256 &other) = delete;

            sha256(sha256 &&other) = delete;

            sha256 &operator=(const sha256 &other) = delete;

            sha256 &operator=(sha256 &&other) = delete;

            sha256() = delete;

            explicit sha256(const std::vector<unsigned char> &data);

            explicit sha256(const std::string &data);

            explicit sha256(const std::wstring &filename);

            ~sha256();

            std::vector<unsigned char> hash();

            std::string hash_string();

            std::wstring hash_wstring();

            DWORD err_code() const;

            std::string err_string() const;

            std::wstring err_wstring() const;
        };
    }
}

#endif //SHA256_H
