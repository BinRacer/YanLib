/* clang-format off */
/*
 * @file http.h
 * @date 2025-04-05
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
#ifndef HTTP_H
#define HTTP_H
#include <Windows.h>
#include <wininet.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "helper/convert.h"
#pragma comment(lib, "wininet.Lib")

namespace YanLib::io {
    class http {
    private:
        HINTERNET internet_handle = nullptr;
        HINTERNET connect_handle = nullptr;
        HINTERNET request_handle = nullptr;
        std::wstring url;
        URL_COMPONENTSW uc = {};
        wchar_t scheme[16] = {};
        wchar_t hostname[128] = {};
        wchar_t username[32] = {};
        wchar_t password[32] = {};
        wchar_t urlpath[512] = {};
        wchar_t extra_info[256] = {};
        bool is_https = false;
        uint16_t port = 0;
        uint32_t error_code = 0;

    public:
        http(const http &other) = delete;

        http(http &&other) = delete;

        http &operator=(const http &other) = delete;

        http &operator=(http &&other) = delete;

        http() = delete;

        explicit http(const std::string &input_url,
                      helper::CodePage code_page = helper::curr_code_page());

        explicit http(const std::wstring &input_url);

        ~http();

        bool url_crack(uint32_t flag = ICU_DECODE | ICU_ESCAPE);

        bool add_header(const char *headers, uint32_t headers_length = -1);

        bool add_header(const wchar_t *headers, uint32_t headers_length = -1);

        bool add_header(const std::string &headers);

        bool add_header(const std::wstring &headers);

        bool add_headers(
                const std::unordered_map<std::string, std::string> &headers);

        bool add_headers(
                const std::unordered_map<std::wstring, std::wstring> &headers);

        bool add_headers(const std::vector<std::string> &headers);

        bool add_headers(const std::vector<std::wstring> &headers);

        bool get_headers(std::unordered_map<std::string, std::string> &headers);

        bool
        get_headers(std::unordered_map<std::wstring, std::wstring> &headers,
                    helper::CodePage code_page = helper::curr_code_page());

        bool get_headers_vec(std::vector<std::string> &headers);

        bool
        get_headers_vec(std::vector<std::wstring> &headers,
                        helper::CodePage code_page = helper::curr_code_page());

        bool
        query_option(uint32_t option, void *buffer, uint32_t *buffer_length);

        bool set_option(uint32_t option, void *buffer, uint32_t buffer_length);

        bool open(const char *agent_name /* "MiniCurl/0.1" */,
                  uint32_t access_type = INTERNET_OPEN_TYPE_PRECONFIG,
                  const char *proxy = nullptr,
                  const char *proxy_bypass = nullptr,
                  uint32_t flag = 0);

        bool open(const wchar_t *agent_name /* L"MiniCurl/0.1" */,
                  uint32_t access_type = INTERNET_OPEN_TYPE_PRECONFIG,
                  const wchar_t *proxy = nullptr,
                  const wchar_t *proxy_bypass = nullptr,
                  uint32_t flag = 0);

        bool connect(uint32_t service = INTERNET_SERVICE_HTTP,
                     uint32_t flag = 0,
                     uintptr_t context = 0);

        bool
        open_request(const char *verb /* "GET" */,
                     const char *version = "HTTP/1.1",
                     const char *referrer = nullptr,
                     const char **accept_types = nullptr,
                     uint32_t flag = INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP |
                             INTERNET_FLAG_KEEP_CONNECTION |
                             INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_NO_COOKIES |
                             INTERNET_FLAG_NO_UI | INTERNET_FLAG_RELOAD,
                     uintptr_t context = 0,
                     helper::CodePage code_page = helper::curr_code_page());

        bool
        open_request(const wchar_t *verb /* L"GET" */,
                     const wchar_t *version = L"HTTP/1.1",
                     const wchar_t *referrer = nullptr,
                     const wchar_t **accept_types = nullptr,
                     uint32_t flag = INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP |
                             INTERNET_FLAG_KEEP_CONNECTION |
                             INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_NO_COOKIES |
                             INTERNET_FLAG_NO_UI | INTERNET_FLAG_RELOAD,
                     uintptr_t context = 0);

        uint32_t get_content_length();

        bool send_request(const char *headers /* nullptr */,
                          uint32_t headers_length /* 0 */,
                          void *optional = nullptr,
                          uint32_t optional_length = 0);

        bool send_request(const wchar_t *headers /* nullptr */,
                          uint32_t headers_length /* 0 */,
                          void *optional = nullptr,
                          uint32_t optional_length = 0);

        bool send_request_ex(INTERNET_BUFFERSW *buffers_in,
                             INTERNET_BUFFERSW *buffers_out = nullptr,
                             uint32_t flag = 0,
                             uintptr_t context = 0);

        bool end_request_ex(INTERNET_BUFFERSW *buffers_out = nullptr,
                            uint32_t flag = 0,
                            uintptr_t context = 0);

        bool read(void *buf, uint32_t size, uint32_t *ret_size);

        std::vector<uint8_t> read_bytes(int32_t buffer_size = 1024);

        bool write(const void *buf, uint32_t size, uint32_t *ret_size);

        uint32_t write_bytes(const std::vector<uint8_t> &vec);

        static std::string read_string_to_end(const std::string &input_url);

        static std::wstring read_wstring_to_end(
                const std::wstring &input_url,
                helper::CodePage code_page = helper::curr_code_page());

        static std::vector<uint8_t>
        read_bytes_to_end(const std::string &input_url);

        static std::vector<uint8_t>
        read_bytes_to_end(const std::wstring &input_url);

        static uint32_t download(const std::string &input_url,
                                 const char *file_name);

        static uint32_t download(const std::wstring &input_url,
                                 const wchar_t *file_name);

        static uint32_t upload(const std::string &input_url,
                               const char *file_name);

        static uint32_t upload(const std::wstring &input_url,
                               const wchar_t *file_name);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::io
#endif // HTTP_H
