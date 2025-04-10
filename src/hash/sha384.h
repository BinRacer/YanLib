//
// Created by forkernel on 2025/4/8.
//

#ifndef SHA384_H
#define SHA384_H
#include <Windows.h>
#include <string>
#include <vector>

namespace YanLib::hash {
    class sha384 {
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
#endif //SHA384_H
