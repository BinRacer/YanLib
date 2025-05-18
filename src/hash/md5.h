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
        HCRYPTPROV crypt_prov_handle;
        HCRYPTHASH crypt_hash_handle;
        std::vector<uint8_t> data_bytes;
        std::vector<uint8_t> hash_bytes;
        std::wstring file_name;
        bool is_file;
        bool is_done = false;
        uint32_t error_code;

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

        explicit md5(const char* filename);

        explicit md5(const wchar_t* filename);

        ~md5();

        std::vector<uint8_t> hash();

        std::string hash_string();

        std::wstring hash_wstring();

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::hash
#endif // MD5_H
