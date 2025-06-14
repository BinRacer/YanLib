/* clang-format off */
/*
 * @file http.cpp
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
#include "http.h"
#include "fs.h"

namespace YanLib::io {
    http::http(const std::string &input_url, helper::CodePage code_page) {
        uc.dwStructSize = sizeof(uc);
        uc.dwSchemeLength = _countof(scheme) - 1;
        uc.dwHostNameLength = _countof(hostname) - 1;
        uc.dwUserNameLength = _countof(username) - 1;
        uc.dwPasswordLength = _countof(password) - 1;
        uc.dwUrlPathLength = _countof(urlpath) - 1;
        uc.dwExtraInfoLength = _countof(extra_info) - 1;
        uc.lpszScheme = scheme;
        uc.lpszHostName = hostname;
        uc.lpszUserName = username;
        uc.lpszPassword = password;
        uc.lpszUrlPath = urlpath;
        uc.lpszExtraInfo = extra_info;
        url = helper::convert::str_to_wstr(input_url, code_page);
    }

    http::http(const std::wstring &input_url) {
        uc.dwStructSize = sizeof(uc);
        uc.dwSchemeLength = _countof(scheme) - 1;
        uc.dwHostNameLength = _countof(hostname) - 1;
        uc.dwUserNameLength = _countof(username) - 1;
        uc.dwPasswordLength = _countof(password) - 1;
        uc.dwUrlPathLength = _countof(urlpath) - 1;
        uc.dwExtraInfoLength = _countof(extra_info) - 1;
        uc.lpszScheme = scheme;
        uc.lpszHostName = hostname;
        uc.lpszUserName = username;
        uc.lpszPassword = password;
        uc.lpszUrlPath = urlpath;
        uc.lpszExtraInfo = extra_info;
        url = input_url;
    }

    http::~http() {
        if (request_handle) {
            InternetCloseHandle(request_handle);
            request_handle = nullptr;
        }
        if (connect_handle) {
            InternetCloseHandle(connect_handle);
            connect_handle = nullptr;
        }
        if (internet_handle) {
            InternetCloseHandle(internet_handle);
            internet_handle = nullptr;
        }
    }

    bool http::url_crack(const uint32_t flag) {
        if (!InternetCrackUrlW(url.data(), url.size(), flag, &uc)) {
            error_code = GetLastError();
            return false;
        }
        port = uc.nPort;
        is_https = _wcsicmp(scheme, L"https") == 0;
        return true;
    }

    bool http::add_header(const char *headers, const uint32_t headers_length) {
        if (!HttpAddRequestHeadersA(request_handle, headers, headers_length,
                                    HTTP_ADDREQ_FLAG_ADD)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::add_header(const wchar_t *headers,
                          const uint32_t headers_length) {
        if (!HttpAddRequestHeadersW(request_handle, headers, headers_length,
                                    HTTP_ADDREQ_FLAG_ADD)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::add_header(const std::string &headers) {
        if (!HttpAddRequestHeadersA(request_handle, headers.data(),
                                    headers.size(), HTTP_ADDREQ_FLAG_ADD)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::add_header(const std::wstring &headers) {
        if (!HttpAddRequestHeadersW(request_handle, headers.data(),
                                    headers.size(), HTTP_ADDREQ_FLAG_ADD)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::add_headers(
            const std::unordered_map<std::string, std::string> &headers) {
        if (headers.empty()) {
            return false;
        }
        for (const auto &[key, value] : headers) {
            std::string line;
            line.append(key);
            line.append(": ");
            line.append(value);
            if (!HttpAddRequestHeadersA(request_handle, line.data(),
                                        line.size(), HTTP_ADDREQ_FLAG_ADD)) {
                error_code = GetLastError();
                return false;
            }
        }
        return true;
    }

    bool http::add_headers(
            const std::unordered_map<std::wstring, std::wstring> &headers) {
        if (headers.empty()) {
            return false;
        }
        for (const auto &[key, value] : headers) {
            std::wstring line;
            line.append(key);
            line.append(L": ");
            line.append(value);
            if (!HttpAddRequestHeadersW(request_handle, line.data(),
                                        line.size(), HTTP_ADDREQ_FLAG_ADD)) {
                error_code = GetLastError();
                return false;
            }
        }
        return true;
    }

    bool http::add_headers(const std::vector<std::string> &headers) {
        if (headers.empty()) {
            return false;
        }
        for (const auto &line : headers) {
            if (!HttpAddRequestHeadersA(request_handle, line.data(),
                                        line.size(), HTTP_ADDREQ_FLAG_ADD)) {
                error_code = GetLastError();
                return false;
            }
        }
        return true;
    }

    bool http::add_headers(const std::vector<std::wstring> &headers) {
        if (headers.empty()) {
            return false;
        }
        for (const auto &line : headers) {
            if (!HttpAddRequestHeadersW(request_handle, line.data(),
                                        line.size(), HTTP_ADDREQ_FLAG_ADD)) {
                error_code = GetLastError();
                return false;
            }
        }
        return true;
    }

    bool
    http::get_headers(std::unordered_map<std::string, std::string> &headers) {
        unsigned long size = 0;
        // first call to fetch the buffer size
        HttpQueryInfoW(request_handle, HTTP_QUERY_RAW_HEADERS_CRLF, nullptr,
                       &size, nullptr);
        error_code = GetLastError();
        if (error_code != ERROR_INSUFFICIENT_BUFFER)
            return false;
        // allocate wide char buffer
        std::vector<wchar_t> buffer(size / sizeof(wchar_t) + 1);
        if (!HttpQueryInfoW(request_handle, HTTP_QUERY_RAW_HEADERS_CRLF,
                            buffer.data(), &size, nullptr)) {
            error_code = GetLastError();
            return false;
        }

        // convert to utf-8
        const int32_t len = WideCharToMultiByte(CP_UTF8, 0, buffer.data(), -1,
                                                nullptr, 0, nullptr, nullptr);
        std::string utf8_str(len, 0);
        WideCharToMultiByte(CP_UTF8, 0, buffer.data(), -1, utf8_str.data(), len,
                            nullptr, nullptr);

        headers.clear();
        // split lines by CRLF
        size_t pos = 0;
        while (pos < utf8_str.size()) {
            const size_t end = utf8_str.find("\r\n", pos);
            if (end == std::string::npos)
                break;

            std::string line = utf8_str.substr(pos, end - pos);
            pos = end + 2;

            if (const size_t colon = line.find(':');
                colon != std::string::npos) {
                std::string key = line.substr(0, colon);
                std::string value = line.substr(colon + 1);

                // standard process: remove space and tolower
                key.erase(std::remove_if(key.begin(), key.end(), isspace),
                          key.end());
                std::transform(key.begin(), key.end(), key.begin(), tolower);

                value.erase(0, value.find_first_not_of(" \t"));
                headers[key] = value;
            }
        }
        return true;
    }

    bool
    http::get_headers(std::unordered_map<std::wstring, std::wstring> &headers,
                      helper::CodePage code_page) {
        std::unordered_map<std::string, std::string> src_map;
        if (!get_headers(src_map))
            return false;
        headers.clear();
        for (const auto &[key, value] : src_map) {
            headers.emplace(helper::convert::str_to_wstr(key, code_page),
                            helper::convert::str_to_wstr(value, code_page));
        }
        return true;
    }

    bool http::get_headers_vec(std::vector<std::string> &headers) {
        unsigned long size = 0;
        // first call to fetch the buffer size
        HttpQueryInfoW(request_handle, HTTP_QUERY_RAW_HEADERS_CRLF, nullptr,
                       &size, nullptr);
        error_code = GetLastError();
        if (error_code != ERROR_INSUFFICIENT_BUFFER)
            return false;

        // allocate wide char buffer
        std::vector<wchar_t> buffer(size / sizeof(wchar_t) + 1);
        if (!HttpQueryInfoW(request_handle, HTTP_QUERY_RAW_HEADERS_CRLF,
                            buffer.data(), &size, nullptr)) {
            error_code = GetLastError();
            return false;
        }

        // convert to utf-8
        const int32_t len = WideCharToMultiByte(CP_UTF8, 0, buffer.data(), -1,
                                                nullptr, 0, nullptr, nullptr);
        std::string utf8_str(len, 0);
        WideCharToMultiByte(CP_UTF8, 0, buffer.data(), -1, utf8_str.data(), len,
                            nullptr, nullptr);

        headers.clear();
        // split lines by CRLF
        size_t pos = 0;
        while (pos < utf8_str.size()) {
            const size_t end = utf8_str.find("\r\n", pos);
            if (end == std::string::npos)
                break;

            std::string line = utf8_str.substr(pos, end - pos);
            pos = end + 2;
            headers.push_back(line);
        }
        return true;
    }

    bool http::get_headers_vec(std::vector<std::wstring> &headers,
                               helper::CodePage code_page) {
        std::vector<std::string> src;
        if (!get_headers_vec(src)) {
            return false;
        }
        headers.clear();
        for (const auto &line : src) {
            headers.push_back(helper::convert::str_to_wstr(line, code_page));
        }
        return true;
    }

    bool
    http::query_option(uint32_t option, void *buffer, uint32_t *buffer_length) {
        if (!buffer_length) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *buffer_length;
        if (!InternetQueryOptionW(request_handle, option, buffer, &temp)) {
            error_code = GetLastError();
            *buffer_length = temp;
            return false;
        }
        *buffer_length = temp;
        return true;
    }

    bool
    http::set_option(uint32_t option, void *buffer, uint32_t buffer_length) {
        if (!InternetSetOptionW(request_handle, option, buffer,
                                buffer_length)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::open(const char *agent_name,
                    const uint32_t access_type,
                    const char *proxy,
                    const char *proxy_bypass,
                    const uint32_t flag) {
        internet_handle = InternetOpenA(agent_name, access_type, proxy,
                                        proxy_bypass, flag);
        if (!internet_handle) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::open(const wchar_t *agent_name,
                    const uint32_t access_type,
                    const wchar_t *proxy,
                    const wchar_t *proxy_bypass,
                    const uint32_t flag) {
        internet_handle = InternetOpenW(agent_name, access_type, proxy,
                                        proxy_bypass, flag);
        if (!internet_handle) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::connect(const uint32_t service,
                       const uint32_t flag,
                       const uintptr_t context) {
        connect_handle =
                InternetConnectW(internet_handle, hostname, port,
                                 wcslen(username) == 0 ? nullptr : username,
                                 wcslen(password) == 0 ? nullptr : password,
                                 service, flag, context);
        if (!connect_handle) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::open_request(const char *verb,
                            const char *version,
                            const char *referrer,
                            const char **accept_types,
                            uint32_t flag,
                            const uintptr_t context,
                            helper::CodePage code_page) {
        if (wcslen(extra_info) > 0) {
            wcscat_s(urlpath, _countof(urlpath) - 1, extra_info);
        }
        const std::string url =
                helper::convert::wstr_to_str(urlpath, code_page);
        if (is_https) {
            flag = flag | INTERNET_FLAG_SECURE |
                    INTERNET_FLAG_IGNORE_CERT_CN_INVALID;
        }
        request_handle =
                HttpOpenRequestA(connect_handle, verb, url.data(), version,
                                 referrer, accept_types, flag, context);
        if (!request_handle) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::open_request(const wchar_t *verb,
                            const wchar_t *version,
                            const wchar_t *referrer,
                            const wchar_t **accept_types,
                            uint32_t flag,
                            const uintptr_t context) {
        if (wcslen(extra_info) > 0) {
            wcscat_s(urlpath, _countof(urlpath) - 1, extra_info);
        }

        if (is_https) {
            flag = flag | INTERNET_FLAG_SECURE |
                    INTERNET_FLAG_IGNORE_CERT_CN_INVALID;
        }

        request_handle =
                HttpOpenRequestW(connect_handle, verb, urlpath, version,
                                 referrer, accept_types, flag, context);
        if (!request_handle) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    uint32_t http::get_content_length() {
        uint32_t content_length = 0;
        unsigned long buffer_size = sizeof(content_length);

        if (constexpr uint32_t flags =
                    HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER;
            !HttpQueryInfoW(request_handle, flags, &content_length,
                            &buffer_size, nullptr)) {
            error_code = GetLastError();
            return 0;
        }
        return content_length;
    }

    // support http and https
    bool http::send_request(const char *headers,
                            const uint32_t headers_length,
                            void *optional,
                            const uint32_t optional_length) {
        if (is_https) {
            bool result = false;
            do {
                uint32_t flags = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
                        SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
                if (!set_option(INTERNET_OPTION_SECURITY_FLAGS, &flags,
                                sizeof(flags))) {
                    break;
                }
                if (!HttpSendRequestA(request_handle, headers, headers_length,
                                      optional, optional_length)) {
                    error_code = GetLastError();
                    break;
                }
                result = true;
            } while (false);
            return result;
        } else {
            if (!HttpSendRequestA(request_handle, headers, headers_length,
                                  optional, optional_length)) {
                error_code = GetLastError();
                return false;
            }
            return true;
        }
    }

    // support http and https
    bool http::send_request(const wchar_t *headers,
                            const uint32_t headers_length,
                            void *optional,
                            const uint32_t optional_length) {
        if (is_https) {
            bool result = false;
            do {
                uint32_t flags = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
                        SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
                if (!set_option(INTERNET_OPTION_SECURITY_FLAGS, &flags,
                                sizeof(flags))) {
                    break;
                }
                if (!HttpSendRequestW(request_handle, headers, headers_length,
                                      optional, optional_length)) {
                    error_code = GetLastError();
                    break;
                }
                result = true;
            } while (false);
            return result;
        } else {
            if (!HttpSendRequestW(request_handle, headers, headers_length,
                                  optional, optional_length)) {
                error_code = GetLastError();
                return false;
            }
            return true;
        }
    }

    // support http and https
    // call send_request_ex(), next must call end_request_ex()
    bool http::send_request_ex(INTERNET_BUFFERSW *buffers_in,
                               INTERNET_BUFFERSW *buffers_out,
                               const uint32_t flag,
                               const uintptr_t context) {
        if (is_https) {
            bool result = false;
            do {
                uint32_t flags = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
                        SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
                if (!set_option(INTERNET_OPTION_SECURITY_FLAGS, &flags,
                                sizeof(flags))) {
                    break;
                }
                if (!HttpSendRequestExW(request_handle, buffers_in, buffers_out,
                                        flag, context)) {
                    error_code = GetLastError();
                    break;
                }
                result = true;
            } while (false);
            return result;
        } else {
            if (!HttpSendRequestExW(request_handle, buffers_in, buffers_out,
                                    flag, context)) {
                error_code = GetLastError();
                return false;
            }
            return true;
        }
    }

    // call send_request_ex(), next must call end_request_ex()
    bool http::end_request_ex(INTERNET_BUFFERSW *buffers_out,
                              const uint32_t flag,
                              const uintptr_t context) {
        if (!HttpEndRequestW(request_handle, buffers_out, flag, context)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::read(void *buf, uint32_t size, uint32_t *ret_size) {
        if (!ret_size) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *ret_size;
        if (!InternetReadFile(request_handle, buf, size, &temp)) {
            error_code = GetLastError();
            *ret_size = temp;
            return false;
        }
        *ret_size = temp;
        return true;
    }

    std::vector<uint8_t> http::read_bytes(int32_t buffer_size) {
        if (buffer_size < 1024) {
            buffer_size = 1024;
        }
        std::vector<uint8_t> raw_data(buffer_size, '\0');
        unsigned long bytes_read = 0;
        if (InternetReadFile(request_handle, raw_data.data(), buffer_size,
                             &bytes_read) &&
            bytes_read > 0) {
            raw_data.resize(bytes_read);
            raw_data.shrink_to_fit();
            return raw_data;
        }
        error_code = GetLastError();
        return {};
    }

    bool http::write(const void *buf, uint32_t size, uint32_t *ret_size) {
        if (!ret_size) {
            error_code = STATUS_ACCESS_VIOLATION;
            return false;
        }
        unsigned long temp = *ret_size;
        if (!InternetWriteFile(request_handle, buf, size, &temp)) {
            error_code = GetLastError();
            *ret_size = temp;
            return false;
        }
        *ret_size = temp;
        return true;
    }

    uint32_t http::write_bytes(const std::vector<uint8_t> &vec) {
        unsigned long bytes_read = 0;
        if (InternetWriteFile(request_handle, vec.data(), vec.size(),
                              &bytes_read) &&
            bytes_read > 0) {
            return bytes_read;
        }
        error_code = GetLastError();
        return 0;
    }

    // avoid read too big file
    std::string http::read_string_to_end(const std::string &input_url) {
        std::string body{};
        do {
            http client(input_url);
            uint32_t content_length = 0;
            if (!client.url_crack()) {
                break;
            }
            if (!client.open(L"MiniCurl/0.1")) {
                break;
            }
            if (!client.connect()) {
                break;
            }
            if (!client.open_request(L"GET")) {
                break;
            }
            if (!client.send_request(static_cast<wchar_t *>(nullptr), 0)) {
                break;
            }

            content_length = client.get_content_length();
            if (content_length <= 0 || content_length >= 5 * 1024 * 1024) {
                break;
            }
            body.resize(content_length);
            uint32_t bytes_read = 0;
            if (!client.read(body.data(), content_length, &bytes_read)) {
                break;
            }
            body.shrink_to_fit();
        } while (false);
        return body;
    }

    // avoid read too big file
    std::wstring http::read_wstring_to_end(const std::wstring &input_url,
                                           helper::CodePage code_page) {
        std::wstring result{};
        do {
            http client(input_url);
            uint32_t content_length = 0;
            if (!client.url_crack()) {
                break;
            }
            if (!client.open(L"MiniCurl/0.1")) {
                break;
            }
            if (!client.connect()) {
                break;
            }
            if (!client.open_request(L"GET")) {
                break;
            }
            if (!client.send_request(static_cast<wchar_t *>(nullptr), 0)) {
                break;
            }

            content_length = client.get_content_length();
            if (content_length <= 0 || content_length >= 5 * 1024 * 1024) {
                break;
            }

            std::string body(content_length, '\0');
            uint32_t bytes_read = 0;
            if (!client.read(body.data(), content_length, &bytes_read)) {
                break;
            }
            body.shrink_to_fit();
            result = helper::convert::str_to_wstr(body, code_page);
        } while (false);
        return result;
    }

    std::vector<uint8_t> http::read_bytes_to_end(const std::string &input_url) {
        std::vector<uint8_t> body{};
        do {
            http client(input_url);
            uint32_t content_length = 0;
            if (!client.url_crack()) {
                break;
            }
            if (!client.open(L"MiniCurl/0.1")) {
                break;
            }
            if (!client.connect()) {
                break;
            }
            if (!client.open_request(L"GET")) {
                break;
            }
            if (!client.send_request(static_cast<wchar_t *>(nullptr), 0)) {
                break;
            }
            content_length = client.get_content_length();
            if (content_length <= 0 || content_length >= 5 * 1024 * 1024) {
                break;
            }
            body.resize(content_length);
            uint32_t bytes_read = 0;
            if (!client.read(body.data(), content_length, &bytes_read)) {
                break;
            }
            body.shrink_to_fit();
        } while (false);
        return body;
    }

    std::vector<uint8_t>
    http::read_bytes_to_end(const std::wstring &input_url) {
        std::vector<uint8_t> body{};
        do {
            http client(input_url);
            uint32_t content_length = 0;
            if (!client.url_crack()) {
                break;
            }
            if (!client.open(L"MiniCurl/0.1")) {
                break;
            }
            if (!client.connect()) {
                break;
            }
            if (!client.open_request(L"GET")) {
                break;
            }
            if (!client.send_request(static_cast<wchar_t *>(nullptr), 0)) {
                break;
            }
            content_length = client.get_content_length();
            if (content_length <= 0 || content_length >= 5 * 1024 * 1024) {
                break;
            }
            body.resize(content_length);
            uint32_t bytes_read = 0;
            if (!client.read(body.data(), content_length, &bytes_read)) {
                break;
            }
            body.shrink_to_fit();
        } while (false);
        return body;
    }

    // support http and https
    uint32_t http::download(const std::string &input_url,
                            const char *file_name) {
        uint32_t error = 0;
        http client(input_url);
        uint32_t content_length = 0;
        fs file(file_name, DesiredAccess::Read | DesiredAccess::Write,
                ShareMode::Read | ShareMode::Write, nullptr,
                CreationDisposition::CreateAlways);
        if (!file.is_ok()) {
            return file.err_code();
        }
        do {
            if (!client.url_crack()) {
                error = client.err_code();
                break;
            }
            if (!client.open(L"MiniCurl/0.1")) {
                error = client.err_code();
                break;
            }
            if (!client.connect()) {
                error = client.err_code();
                break;
            }
            if (!client.open_request(L"GET")) {
                error = client.err_code();
                break;
            }
            if (!client.send_request(static_cast<wchar_t *>(nullptr), 0)) {
                error = client.err_code();
                break;
            }
            content_length = client.get_content_length();
            if (content_length <= 0) {
                error = client.err_code();
                break;
            }

            constexpr uint32_t buf_size = 4096;
            std::vector<uint8_t> buf(buf_size, '\0');
            uint32_t bytes_read = 0;
            uint32_t bytes_written = 0;
            do {
                if (!client.read(buf.data(), buf_size, &bytes_read)) {
                    error = client.err_code();
                    break;
                }
                if (bytes_read <= 0)
                    break;
                if (!file.write(buf.data(), bytes_read, &bytes_written)) {
                    error = file.err_code();
                    break;
                }
            } while (bytes_read > 0 && bytes_written > 0);
        } while (false);
        return error;
    }

    // support http and https
    uint32_t http::download(const std::wstring &input_url,
                            const wchar_t *file_name) {
        uint32_t error = 0;
        http client(input_url);
        uint32_t content_length = 0;
        fs file(file_name, DesiredAccess::Read | DesiredAccess::Write,
                ShareMode::Read | ShareMode::Write, nullptr,
                CreationDisposition::CreateAlways);
        if (!file.is_ok()) {
            return file.err_code();
        }
        do {
            if (!client.url_crack()) {
                error = client.err_code();
                break;
            }
            if (!client.open(L"MiniCurl/0.1")) {
                error = client.err_code();
                break;
            }
            if (!client.connect()) {
                error = client.err_code();
                break;
            }
            if (!client.open_request(L"GET")) {
                error = client.err_code();
                break;
            }
            if (!client.send_request(static_cast<wchar_t *>(nullptr), 0)) {
                error = client.err_code();
                break;
            }
            content_length = client.get_content_length();
            if (content_length <= 0) {
                error = client.err_code();
                break;
            }

            constexpr uint32_t buf_size = 4096;
            std::vector<uint8_t> buf(buf_size, '\0');
            uint32_t bytes_read = 0;
            uint32_t bytes_written = 0;
            do {
                if (!client.read(buf.data(), buf_size, &bytes_read)) {
                    error = client.err_code();
                    break;
                }
                if (bytes_read <= 0)
                    break;
                if (!file.write(buf.data(), bytes_read, &bytes_written)) {
                    error = file.err_code();
                    break;
                }
            } while (bytes_read > 0 && bytes_written > 0);
        } while (false);
        return error;
    }

    // support http and https
    uint32_t http::upload(const std::string &input_url, const char *file_name) {
        uint32_t error = 0;
        http client(input_url);
        fs file(file_name);
        if (!file.is_ok()) {
            return file.err_code();
        }
        do {
            if (!client.url_crack()) {
                error = client.err_code();
                break;
            }
            if (!client.open("MiniUpload/0.1")) {
                error = client.err_code();
                break;
            }
            if (!client.connect()) {
                error = client.err_code();
                break;
            }
            if (!client.open_request("POST")) {
                error = client.err_code();
                break;
            }
            if (!client.add_header("Content-Type: application/octet-stream; "
                                   "charset=utf-8")) {
                error = client.err_code();
                break;
            }

            INTERNET_BUFFERSW buffers_in = {};
            buffers_in.dwStructSize = sizeof(INTERNET_BUFFERSW);
            buffers_in.dwBufferTotal = file.size();
            if (!client.send_request_ex(&buffers_in, nullptr, 0, 0)) {
                error = client.err_code();
                break;
            }

            constexpr uint32_t buf_size = 4096;
            std::vector<uint8_t> buf(buf_size, '\0');
            uint32_t bytes_read = 0;
            uint32_t bytes_written = 0;
            do {
                if (!file.read(buf.data(), bytes_read, &bytes_read)) {
                    error = file.err_code();
                    break;
                }
                if (bytes_read <= 0)
                    break;
                if (!client.write(buf.data(), bytes_read, &bytes_written)) {
                    error = client.err_code();
                    break;
                }
            } while (bytes_read > 0 && bytes_written > 0);
            if (!client.end_request_ex()) {
                error = client.err_code();
            }
        } while (false);
        return error;
    }

    // support http and https
    uint32_t http::upload(const std::wstring &input_url,
                          const wchar_t *file_name) {
        uint32_t error = 0;
        http client(input_url);
        fs file(file_name);
        if (!file.is_ok()) {
            return file.err_code();
        }
        do {
            if (!client.url_crack()) {
                error = client.err_code();
                break;
            }
            if (!client.open(L"MiniUpload/0.1")) {
                error = client.err_code();
                break;
            }
            if (!client.connect()) {
                error = client.err_code();
                break;
            }
            if (!client.open_request(L"POST")) {
                error = client.err_code();
                break;
            }
            if (!client.add_header(L"Content-Type: application/octet-stream; "
                                   L"charset=utf-8")) {
                error = client.err_code();
                break;
            }

            INTERNET_BUFFERSW buffers_in = {};
            buffers_in.dwStructSize = sizeof(INTERNET_BUFFERSW);
            buffers_in.dwBufferTotal = file.size();
            if (!client.send_request_ex(&buffers_in, nullptr, 0, 0)) {
                error = client.err_code();
                break;
            }

            constexpr uint32_t buf_size = 4096;
            std::vector<uint8_t> buf(buf_size, '\0');
            uint32_t bytes_read = 0;
            uint32_t bytes_written = 0;
            do {
                if (!file.read(buf.data(), bytes_read, &bytes_read)) {
                    error = file.err_code();
                    break;
                }
                if (bytes_read <= 0)
                    break;
                if (!client.write(buf.data(), bytes_read, &bytes_written)) {
                    error = client.err_code();
                    break;
                }
            } while (bytes_read > 0 && bytes_written > 0);
            if (!client.end_request_ex()) {
                error = client.err_code();
            }
        } while (false);
        return error;
    }

    uint32_t http::err_code() const {
        return error_code;
    }

    std::string http::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring http::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::io
