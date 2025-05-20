//
// Created by forkernel on 2025/4/8.
//

#ifndef SHA512_H
#define SHA512_H
#include <Windows.h>
#include <string>
#include <vector>

namespace YanLib::hash {
    class sha512 {
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
        sha512(const sha512 &other) = delete;

        sha512(sha512 &&other) = delete;

        sha512 &operator=(const sha512 &other) = delete;

        sha512 &operator=(sha512 &&other) = delete;

        sha512() = delete;

        explicit sha512(const std::vector<uint8_t> &data);

        explicit sha512(const std::string &data);

        explicit sha512(const char *filename);

        explicit sha512(const wchar_t *filename);

        ~sha512();

        std::vector<uint8_t> hash();

        std::string hash_string();

        std::wstring hash_wstring();

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::hash
#endif // SHA512_H
