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
        private:
            HCRYPTPROV hCryptProv;
            HCRYPTHASH hCryptHash;
            std::vector<unsigned char> data_bytes;
            std::vector<unsigned char> hash_bytes;
            std::wstring file_name;
            bool isFile;
            DWORD error_code;

            static std::string format_hex_fast(const std::vector<unsigned char> &data);

            bool pre_process();

            bool process_file();

            bool process_data();

            std::vector<unsigned char> process();

            bool post_process();

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
