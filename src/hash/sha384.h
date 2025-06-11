/* clang-format off */
/*
 * @file sha384.h
 * @date 2025-04-08
 * @license MIT License
 *
 * Copyright (c) 2025 BinRacer <native.lab@outlook.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* clang-format on */
#ifndef SHA384_H
#define SHA384_H
#include <Windows.h>
#include <string>
#include <vector>
#include "helper/convert.h"

namespace YanLib::hash {
    class sha384 {
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
        sha384(const sha384 &other) = delete;

        sha384(sha384 &&other) = delete;

        sha384 &operator=(const sha384 &other) = delete;

        sha384 &operator=(sha384 &&other) = delete;

        sha384() = delete;

        explicit sha384(const std::vector<uint8_t> &data);

        explicit sha384(const std::string &data);

        explicit sha384(const char *filename,
                        helper::CodePage code_page = helper::curr_code_page());

        explicit sha384(const wchar_t *filename);

        ~sha384();

        std::vector<uint8_t> hash();

        std::string hash_string();

        std::wstring
        hash_wstring(helper::CodePage code_page = helper::curr_code_page());

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::hash
#endif // SHA384_H
