//
// Created by forkernel on 2025/4/7.
//

#ifndef MD5_H
#define MD5_H
#include <Windows.h>
#include <string>
#include <vector>

namespace YanLib::hash {
    class md5 {
    private:
        HCRYPTPROV hCryptProv;
        HCRYPTHASH hCryptHash;
        std::vector<unsigned char> data_bytes;
        std::vector<unsigned char> hash_bytes;
        std::wstring file_name;
        bool isFile;
        bool isDone = false;
        DWORD error_code;

        static std::string format_hex_fast(const std::vector<unsigned char> &data);

        bool pre_process();

        bool process_file();

        bool process_data();

        std::vector<unsigned char> process();

        bool post_process();

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
#endif //MD5_H
