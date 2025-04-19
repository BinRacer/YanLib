//
// Created by forkernel on 2025/4/8.
//

#ifndef SHA256_H
#define SHA256_H
#include <Windows.h>
#include <string>
#include <vector>

namespace YanLib::hash {
    class sha256 {
    private:
        HCRYPTPROV crypt_prov_handle;
        HCRYPTHASH crypt_hash_handle;
        std::vector<uint8_t> data_bytes;
        std::vector<uint8_t> hash_bytes;
        std::wstring file_name;
        bool is_file;
        bool is_done = false;
        DWORD error_code;

        static std::string format_hex_fast(const std::vector<uint8_t> &data);

        bool pre_process();

        bool process_file();

        bool process_data();

        std::vector<uint8_t> process();

        bool post_process();

    public:
        sha256(const sha256 &other) = delete;

        sha256(sha256 &&other) = delete;

        sha256 &operator=(const sha256 &other) = delete;

        sha256 &operator=(sha256 &&other) = delete;

        sha256() = delete;

        explicit sha256(const std::vector<uint8_t> &data);

        explicit sha256(const std::string &data);

        explicit sha256(const std::wstring &filename);

        ~sha256();

        std::vector<uint8_t> hash();

        std::string hash_string();

        std::wstring hash_wstring();

        DWORD err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}
#endif //SHA256_H
