//
// Created by forkernel on 2025/4/5.
//

#ifndef HTTP_H
#define HTTP_H
#include <Windows.h>
#include <WinInet.h>
#include <string>
#include <vector>
#include <unordered_map>
#pragma comment(lib, "WinInet.lib")

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
        DWORD error_code = 0;

    public:
        http(const http &other) = delete;

        http(http &&other) = delete;

        http &operator=(const http &other) = delete;

        http &operator=(http &&other) = delete;

        http() = delete;

        explicit http(const std::wstring &input_url);

        ~http();

        bool url_crack(DWORD flag = ICU_DECODE | ICU_ESCAPE);

        bool add_header(const wchar_t *headers,
                        DWORD headers_length = -1);

        bool add_header(std::string headers);

        bool add_header(std::wstring headers);

        bool add_headers(std::unordered_map<std::string, std::string> &map);

        bool add_headers(std::unordered_map<std::wstring, std::wstring> &map);

        bool add_headers(std::vector<std::string> &vec);

        bool add_headers(std::vector<std::wstring> &vec);

        std::unordered_map<std::string, std::string> get_headers() const;

        std::unordered_map<std::wstring, std::wstring> get_headers_wide() const;

        std::vector<std::string> get_headers_vec() const;

        std::vector<std::wstring> get_headers_vec_wide() const;

        bool query_option(DWORD option,
                          void* buffer,
                          LPDWORD buffer_length);

        bool set_option(DWORD option,
                        void* buffer,
                        DWORD buffer_length);

        bool open(const wchar_t *agent_name = L"MiniCurl/0.1",
                  DWORD access_type = INTERNET_OPEN_TYPE_PRECONFIG,
                  const wchar_t *proxy = nullptr,
                  const wchar_t *proxy_bypass = nullptr,
                  DWORD flag = 0);

        bool connect(DWORD service = INTERNET_SERVICE_HTTP,
                     DWORD flag = 0,
                     DWORD_PTR context = 0);

        bool open_request(const wchar_t *verb = L"GET",
                          const wchar_t *version = L"HTTP/1.1",
                          const wchar_t *referrer = nullptr,
                          const wchar_t **accept_types = nullptr,
                          DWORD flag = INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP |
                                       INTERNET_FLAG_KEEP_CONNECTION |
                                       INTERNET_FLAG_NO_AUTH |
                                       INTERNET_FLAG_NO_COOKIES |
                                       INTERNET_FLAG_NO_UI |
                                       INTERNET_FLAG_RELOAD,
                          DWORD_PTR context = 0);


        DWORD get_content_length();

        bool send_request(const wchar_t *headers = nullptr,
                          DWORD headers_length = 0,
                          void* optional = nullptr,
                          DWORD optional_length = 0);

        bool send_request_ex(LPINTERNET_BUFFERSW buffers_in,
                             LPINTERNET_BUFFERSW buffers_out = nullptr,
                             DWORD flag = 0,
                             DWORD_PTR context = 0);

        bool end_request_ex(LPINTERNET_BUFFERSW buffers_out = nullptr,
                            DWORD flag = 0,
                            DWORD_PTR context = 0);

        bool read(void* buf,
                  DWORD size,
                  LPDWORD ret_size);

        std::vector<uint8_t> read_bytes(int32_t buffer_size = 1024);

        bool write(LPCVOID buf,
                   DWORD size,
                   LPDWORD ret_size);

        DWORD write_bytes(std::vector<uint8_t> &vec);

        static std::string read_string_to_end(const std::wstring &input_url);

        static std::wstring read_wstring_to_end(const std::wstring &input_url);

        static std::vector<uint8_t> read_bytes_to_end(
            const std::wstring &input_url);

        static DWORD download(const std::wstring &input_url,
                              const wchar_t *file_name);

        static DWORD upload(const std::wstring &input_url,
                            const wchar_t *file_name);

        DWORD err_code() const;

        std::string err_string() const;

        std::wstring err_wstring() const;
    };
}
#endif //HTTP_H
