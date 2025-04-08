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

namespace YanLib {
    namespace io {
        class http {
        public:
            http(const http &other) = delete;

            http(http &&other) = delete;

            http &operator=(const http &other) = delete;

            http &operator=(http &&other) = delete;

            http() = delete;

            explicit http(const std::wstring &input_url);

            ~http();

            bool url_crack(DWORD dwFlags = ICU_DECODE | ICU_ESCAPE);

            bool add_header(const wchar_t *lpszHeaders,
                            DWORD dwHeadersLength = -1);

            bool add_header(std::string lpszHeaders);

            bool add_header(std::wstring lpszHeaders);

            bool add_headers(std::unordered_map<std::string, std::string> &map);

            bool add_headers(std::unordered_map<std::wstring, std::wstring> &map);

            bool add_headers(std::vector<std::string> &vec);

            bool add_headers(std::vector<std::wstring> &vec);

            std::unordered_map<std::string, std::string> get_headers() const;

            std::unordered_map<std::wstring, std::wstring> get_headers_wide() const;

            std::vector<std::string> get_headers_vec() const;

            std::vector<std::wstring> get_headers_vec_wide() const;

            bool query_option(DWORD dwOption,
                              LPVOID lpBuffer,
                              LPDWORD lpdwBufferLength);

            bool set_option(DWORD dwOption,
                            LPVOID lpBuffer,
                            DWORD dwBufferLength);

            bool open(const wchar_t *lpszAgent = L"MiniCurl/0.1",
                      DWORD dwAccessType = INTERNET_OPEN_TYPE_PRECONFIG,
                      const wchar_t *lpszProxy = nullptr,
                      const wchar_t *lpszProxyBypass = nullptr,
                      DWORD dwFlags = 0);

            bool connect(DWORD dwService = INTERNET_SERVICE_HTTP,
                         DWORD dwFlags = 0,
                         DWORD_PTR dwContext = 0);

            bool open_request(const wchar_t *lpszVerb = L"GET",
                              const wchar_t *lpszVersion = L"HTTP/1.1",
                              const wchar_t *lpszReferrer = nullptr,
                              const wchar_t **lplpszAcceptTypes = nullptr,
                              DWORD dwFlags = INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP |
                                              INTERNET_FLAG_KEEP_CONNECTION |
                                              INTERNET_FLAG_NO_AUTH |
                                              INTERNET_FLAG_NO_COOKIES |
                                              INTERNET_FLAG_NO_UI |
                                              INTERNET_FLAG_RELOAD,
                              DWORD_PTR dwContext = 0);

            DWORD get_content_length();

            bool send_request(const wchar_t *lpszHeaders = nullptr,
                              DWORD dwHeadersLength = 0,
                              LPVOID lpOptional = nullptr,
                              DWORD dwOptionalLength = 0);

            bool send_request_ex(LPINTERNET_BUFFERSW lpBuffersIn,
                                 LPINTERNET_BUFFERSW lpBuffersOut = nullptr,
                                 DWORD dwFlags = 0,
                                 DWORD_PTR dwContext = 0);

            bool end_request_ex(LPINTERNET_BUFFERSW lpBuffersOut = nullptr,
                                DWORD dwFlags = 0,
                                DWORD_PTR dwContext = 0);

            bool read(LPVOID lpBuffer,
                      DWORD dwNumberOfBytesToRead,
                      LPDWORD lpdwNumberOfBytesRead);

            std::vector<unsigned char> read_bytes(int32_t bufferSize = 1024);

            bool write(LPCVOID lpBuffer,
                       DWORD dwNumberOfBytesToWrite,
                       LPDWORD lpdwNumberOfBytesWritten);

            DWORD write_bytes(std::vector<unsigned char> &vec);

            static std::string read_string_to_end(const std::wstring &input_url);

            static std::wstring read_wstring_to_end(const std::wstring &input_url);

            static std::vector<unsigned char> read_bytes_to_end(
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
}
#endif //HTTP_H
