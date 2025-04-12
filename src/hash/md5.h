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
        std::vector<uint8_t> data_bytes;
        std::vector<uint8_t> hash_bytes;
        std::wstring file_name;
        bool isFile;
        bool isDone = false;
        DWORD error_code;

        static std::string format_hex_fast(const std::vector<uint8_t> &data);

        bool pre_process();

        bool process_file();

        bool process_data();

        std::vector<uint8_t> process();

        bool post_process();

    public:
        md5(const md5 &other) = delete;

        md5(md5 &&other) = delete;

        md5 &operator=(const md5 &other) = delete;

        md5 &operator=(md5 &&other) = delete;

        md5() = delete;

        explicit md5(const std::vector<uint8_t> &data);

        explicit md5(const std::string &data);

        explicit md5(const std::wstring &filename);

        ~md5();

        std::vector<uint8_t> hash();

        std::string hash_string();

        std::wstring hash_wstring();

        DWORD err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}
#endif //MD5_H
