//
// Created by forkernel on 2025/4/8.
//

#ifndef SHA384_H
#define SHA384_H
#include <Windows.h>
#include <string>
#include <vector>

namespace YanLib {
    namespace crypto {
        class sha384 {
        public:
            sha384(const sha384 &other) = delete;

            sha384(sha384 &&other) = delete;

            sha384 &operator=(const sha384 &other) = delete;

            sha384 &operator=(sha384 &&other) = delete;

            sha384() = delete;

            explicit sha384(const std::vector<unsigned char> &data);

            explicit sha384(const std::string &data);

            explicit sha384(const std::wstring &filename);

            ~sha384();

            std::vector<unsigned char> hash();

            std::string hash_string();

            std::wstring hash_wstring();

            DWORD err_code() const;

            std::string err_string() const;

            std::wstring err_wstring() const;
        };
    }
}

#endif //SHA384_H
