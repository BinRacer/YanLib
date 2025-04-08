//
// Created by forkernel on 2025/4/7.
//

#ifndef MD5_H
#define MD5_H
#include <Windows.h>
#include <string>
#include <vector>

namespace YanLib {
    namespace crypto {
        class md5 {
        public:
            md5(const md5 &other) = delete;

            md5(md5 &&other) = delete;

            md5 &operator=(const md5 &other) = delete;

            md5 &operator=(md5 &&other) = delete;

            md5() = delete;

            explicit md5(const std::vector<unsigned char> &data);

            explicit md5(const std::string &data);

            explicit md5(const std::wstring &filename);

            ~md5();

            std::vector<unsigned char> hash();

            std::string hash_string();

            std::wstring hash_wstring();

            DWORD err_code() const;

            std::string err_string() const;

            std::wstring err_wstring() const;
        };
    }
}
#endif //MD5_H
