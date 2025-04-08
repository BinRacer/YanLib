//
// Created by forkernel on 2025/4/8.
//

#ifndef SHA1_H
#define SHA1_H
#include <Windows.h>
#include <string>
#include <vector>
namespace YanLib {
    namespace crypto {
        class sha1 {
        public:
            sha1(const sha1 &other) = delete;

            sha1(sha1 &&other) = delete;

            sha1 &operator=(const sha1 &other) = delete;

            sha1 &operator=(sha1 &&other) = delete;

            sha1() = delete;

            explicit sha1(const std::vector<unsigned char> &data);

            explicit sha1(const std::string &data);

            explicit sha1(const std::wstring &filename);

            ~sha1();

            std::vector<unsigned char> hash();

            std::string hash_string();

            std::wstring hash_wstring();

            DWORD err_code() const;

            std::string err_string() const;

            std::wstring err_wstring() const;
        };
    }
}

#endif //SHA1_H
