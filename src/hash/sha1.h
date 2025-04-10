//
// Created by forkernel on 2025/4/8.
//

#ifndef SHA1_H
#define SHA1_H
#include <Windows.h>
#include <string>
#include <vector>

namespace YanLib::hash {
    class sha1 {
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
#endif //SHA1_H
