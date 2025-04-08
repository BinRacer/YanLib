//
// Created by forkernel on 2025/4/8.
//

#ifndef SHA512_H
#define SHA512_H
#include <Windows.h>
#include <string>
#include <vector>
namespace YanLib {
    namespace crypto {
        class sha512 {
        public:
            sha512(const sha512 &other) = delete;

            sha512(sha512 &&other) = delete;

            sha512 &operator=(const sha512 &other) = delete;

            sha512 &operator=(sha512 &&other) = delete;

            sha512() = delete;

            explicit sha512(const std::vector<unsigned char> &data);

            explicit sha512(const std::string &data);

            explicit sha512(const std::wstring &filename);

            ~sha512();

            std::vector<unsigned char> hash();

            std::string hash_string();

            std::wstring hash_wstring();

            DWORD err_code() const;

            std::string err_string() const;

            std::wstring err_wstring() const;
        };
    }
}

#endif //SHA512_H
