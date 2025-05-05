//
// Created by forkernel on 2025/4/5.
//

#include "http.h"
#include "helper/convert.h"
#include "fs.h"

namespace YanLib::io {
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

    bool http::url_crack(unsigned long flag) {
        if (!InternetCrackUrlW(
            url.data(),
            url.size(),
            flag,
            &uc)) {
            error_code = GetLastError();
            return false;
        }
        port = uc.nPort;
        is_https = _wcsicmp(scheme, L"https") == 0;
        return true;
    }

    bool http::add_header(const wchar_t *headers,
                          unsigned long headers_length) {
        if (!HttpAddRequestHeadersW(request_handle,
                                    headers,
                                    headers_length,
                                    HTTP_ADDREQ_FLAG_ADD)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::add_header(const std::string &headers) {
        std::wstring line = helper::convert::str_to_wstr(headers);
        if (!HttpAddRequestHeadersW(request_handle,
                                    line.data(),
                                    line.size(),
                                    HTTP_ADDREQ_FLAG_ADD)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::add_header(std::wstring headers) {
        if (!HttpAddRequestHeadersW(request_handle,
                                    headers.data(),
                                    headers.size(),
                                    HTTP_ADDREQ_FLAG_ADD)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::add_headers(std::unordered_map<std::string, std::string> &map) {
        if (map.empty()) {
            return false;
        }
        for (const auto &pair: map) {
            std::wstring key = helper::convert::str_to_wstr(pair.first);
            std::wstring value = helper::convert::str_to_wstr(pair.second);
            std::wstring line = key + L": " + value;
            if (!HttpAddRequestHeadersW(request_handle,
                                        line.data(),
                                        line.size(),
                                        HTTP_ADDREQ_FLAG_ADD)) {
                error_code = GetLastError();
                return false;
            }
        }
        return true;
    }

    bool http::add_headers(std::unordered_map<std::wstring, std::wstring> &map) {
        if (map.empty()) {
            return false;
        }
        for (const auto &pair: map) {
            std::wstring key = pair.first;
            std::wstring value = pair.second;
            std::wstring line = key + L": " + value;
            if (!HttpAddRequestHeadersW(request_handle,
                                        line.data(),
                                        line.size(),
                                        HTTP_ADDREQ_FLAG_ADD)) {
                error_code = GetLastError();
                return false;
            }
        }
        return true;
    }

    bool http::add_headers(std::vector<std::string> &vec) {
        if (vec.empty()) {
            return false;
        }
        for (const auto &ele: vec) {
            std::wstring line = helper::convert::str_to_wstr(ele);
            if (!HttpAddRequestHeadersW(request_handle,
                                        line.data(),
                                        line.size(),
                                        HTTP_ADDREQ_FLAG_ADD)) {
                error_code = GetLastError();
                return false;
            }
        }
        return true;
    }

    bool http::add_headers(std::vector<std::wstring> &vec) {
        if (vec.empty()) {
            return false;
        }
        for (const auto &line: vec) {
            if (!HttpAddRequestHeadersW(request_handle,
                                        line.data(),
                                        line.size(),
                                        HTTP_ADDREQ_FLAG_ADD)) {
                error_code = GetLastError();
                return false;
            }
        }
        return true;
    }


    std::unordered_map<std::string, std::string> http::get_headers() const {
        std::unordered_map<std::string, std::string> headers;
        unsigned long size = 0;

        // first call to fetch the buffer size
        HttpQueryInfoW(request_handle,
                       HTTP_QUERY_RAW_HEADERS_CRLF,
                       nullptr,
                       &size,
                       nullptr);
        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) return headers;

        // allocate wide char buffer
        std::vector<wchar_t> buffer(size / sizeof(wchar_t) + 1);
        if (!HttpQueryInfoW(request_handle,
                            HTTP_QUERY_RAW_HEADERS_CRLF,
                            buffer.data(),
                            &size,
                            nullptr)) {
            return headers;
        }

        // convert to utf-8
        int len = WideCharToMultiByte(CP_UTF8,
                                      0,
                                      buffer.data(),
                                      -1,
                                      nullptr,
                                      0,
                                      nullptr,
                                      nullptr);
        std::string utf8_str(len, 0);
        WideCharToMultiByte(CP_UTF8,
                            0,
                            buffer.data(),
                            -1,
                            utf8_str.data(),
                            len,
                            nullptr,
                            nullptr);

        // split lines by CRLF
        size_t pos = 0;
        while (pos < utf8_str.size()) {
            size_t end = utf8_str.find("\r\n", pos);
            if (end == std::string::npos) break;

            std::string line = utf8_str.substr(pos, end - pos);
            pos = end + 2;

            size_t colon = line.find(':');
            if (colon != std::string::npos) {
                std::string key = line.substr(0, colon);
                std::string value = line.substr(colon + 1);

                // standard process: remove space and tolower
                key.erase(
                    std::remove_if(key.begin(), key.end(),
                                   isspace),
                    key.end());
                std::transform(
                    key.begin(), key.end(),
                    key.begin(), tolower);

                value.erase(0, value.find_first_not_of(" \t"));
                headers[key] = value;
            }
        }
        return headers;
    }

    std::unordered_map<std::wstring, std::wstring> http::get_headers_wide() const {
        std::unordered_map<std::string, std::string> src_map = get_headers();
        if (src_map.empty()) {
            return {};
        }
        std::unordered_map<std::wstring, std::wstring> dst_map;
        for (const auto &pair: src_map) {
            std::wstring key = helper::convert::str_to_wstr(pair.first);
            std::wstring value = helper::convert::str_to_wstr(pair.second);
            dst_map.emplace(std::move(key), std::move(value));
        }
        return dst_map;
    }

    std::vector<std::string> http::get_headers_vec() const {
        std::vector<std::string> headers;
        unsigned long size = 0;

        // first call to fetch the buffer size
        HttpQueryInfoW(request_handle,
                       HTTP_QUERY_RAW_HEADERS_CRLF,
                       nullptr,
                       &size,
                       nullptr);
        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) return headers;

        // allocate wide char buffer
        std::vector<wchar_t> buffer(size / sizeof(wchar_t) + 1);
        if (!HttpQueryInfoW(request_handle,
                            HTTP_QUERY_RAW_HEADERS_CRLF,
                            buffer.data(),
                            &size,
                            nullptr)) {
            return headers;
        }

        // convert to utf-8
        int len = WideCharToMultiByte(CP_UTF8,
                                      0,
                                      buffer.data(),
                                      -1,
                                      nullptr,
                                      0,
                                      nullptr,
                                      nullptr);
        std::string utf8_str(len, 0);
        WideCharToMultiByte(CP_UTF8,
                            0,
                            buffer.data(),
                            -1,
                            utf8_str.data(),
                            len,
                            nullptr,
                            nullptr);

        // split lines by CRLF
        size_t pos = 0;
        while (pos < utf8_str.size()) {
            size_t end = utf8_str.find("\r\n", pos);
            if (end == std::string::npos) break;

            std::string line = utf8_str.substr(pos, end - pos);
            pos = end + 2;
            headers.push_back(line);
        }
        return headers;
    }

    std::vector<std::wstring> http::get_headers_vec_wide() const {
        std::vector<std::string> src = get_headers_vec();
        if (src.empty()) {
            return {};
        }
        std::vector<std::wstring> dst;
        for (const auto &line: src) {
            dst.push_back(helper::convert::str_to_wstr(line));
        }
        return dst;
    }

    bool http::query_option(unsigned long option,
                            void *buffer,
                            unsigned long *buffer_length) {
        if (!InternetQueryOptionW(request_handle,
                                  option,
                                  buffer,
                                  buffer_length)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::set_option(unsigned long option,
                          void *buffer,
                          unsigned long buffer_length) {
        if (!InternetSetOptionW(request_handle,
                                option,
                                buffer,
                                buffer_length)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::open(const wchar_t *agent_name,
                    unsigned long access_type,
                    const wchar_t *proxy,
                    const wchar_t *proxy_bypass,
                    unsigned long flag) {
        internet_handle = InternetOpenW(agent_name,
                                        access_type,
                                        proxy,
                                        proxy_bypass,
                                        flag);
        if (!internet_handle) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::connect(unsigned long service,
                       unsigned long flag,
                       DWORD_PTR context) {
        connect_handle = InternetConnectW(internet_handle,
                                          hostname,
                                          port,
                                          wcslen(username) == 0
                                              ? nullptr
                                              : username,
                                          wcslen(password) == 0
                                              ? nullptr
                                              : password,
                                          service,
                                          flag,
                                          context);
        if (!connect_handle) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::open_request(const wchar_t *verb,
                            const wchar_t *version,
                            const wchar_t *referrer,
                            const wchar_t **accept_types,
                            unsigned long flag,
                            DWORD_PTR context) {
        if (wcslen(extra_info) > 0) {
            wcscat_s(urlpath, _countof(urlpath) - 1, extra_info);
        }

        if (is_https) {
            flag = flag |
                   INTERNET_FLAG_SECURE |
                   INTERNET_FLAG_IGNORE_CERT_CN_INVALID;
        }

        request_handle = HttpOpenRequestW(connect_handle,
                                          verb,
                                          urlpath,
                                          version,
                                          referrer,
                                          accept_types,
                                          flag,
                                          context);
        if (!request_handle) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    unsigned long http::get_content_length() {
        unsigned long content_length = 0;
        unsigned long buffer_size = sizeof(content_length);
        unsigned long flags = HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER;

        if (!HttpQueryInfoW(request_handle,
                            flags,
                            &content_length,
                            &buffer_size,
                            nullptr)) {
            error_code = GetLastError();
            return 0;
        }
        return content_length;
    }

    // support http and https
    bool http::send_request(const wchar_t *headers,
                            unsigned long headers_length,
                            void *optional,
                            unsigned long optional_length) {
        if (is_https) {
            do {
                unsigned long flags = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
                                      SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
                if (!set_option(INTERNET_OPTION_SECURITY_FLAGS,
                                &flags,
                                sizeof(flags))) {
                    break;
                }
                if (!HttpSendRequestW(request_handle,
                                      headers,
                                      headers_length,
                                      optional,
                                      optional_length)) {
                    error_code = GetLastError();
                    break;
                }
                return true;
            } while (false);
            return false;
        } else {
            if (!HttpSendRequestW(request_handle,
                                  headers,
                                  headers_length,
                                  optional,
                                  optional_length)) {
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
                               unsigned long flag,
                               DWORD_PTR context) {
        if (is_https) {
            do {
                unsigned long flags = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
                                      SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
                if (!set_option(INTERNET_OPTION_SECURITY_FLAGS,
                                &flags,
                                sizeof(flags))) {
                    break;
                }
                if (!HttpSendRequestExW(request_handle,
                                        buffers_in,
                                        buffers_out,
                                        flag,
                                        context)) {
                    error_code = GetLastError();
                    break;
                }
                return true;
            } while (false);
            return false;
        } else {
            if (!HttpSendRequestExW(request_handle,
                                    buffers_in,
                                    buffers_out,
                                    flag,
                                    context)) {
                error_code = GetLastError();
                return false;
            }
            return true;
        }
    }

    // call send_request_ex(), next must call end_request_ex()
    bool http::end_request_ex(INTERNET_BUFFERSW *buffers_out,
                              unsigned long flag,
                              DWORD_PTR context) {
        if (!HttpEndRequestW(request_handle, buffers_out, flag, context)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::read(void *buf,
                    unsigned long size,
                    unsigned long *ret_size) {
        if (!InternetReadFile(request_handle,
                              buf,
                              size,
                              ret_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    std::vector<uint8_t> http::read_bytes(int32_t buffer_size) {
        if (buffer_size < 1024) {
            buffer_size = 1024;
        }
        std::vector<uint8_t> raw_data(buffer_size, '\0');
        unsigned long bytes_read = 0;
        if (InternetReadFile(request_handle,
                             raw_data.data(),
                             buffer_size,
                             &bytes_read) && bytes_read > 0) {
            raw_data.resize(bytes_read);
            raw_data.shrink_to_fit();
            return raw_data;
        }
        error_code = GetLastError();
        return {};
    }

    bool http::write(const void *buf,
                     unsigned long size,
                     unsigned long *ret_size) {
        if (!InternetWriteFile(request_handle,
                               buf,
                               size,
                               ret_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    unsigned long http::write_bytes(std::vector<uint8_t> &vec) {
        unsigned long bytes_read = 0;
        if (InternetWriteFile(request_handle,
                              vec.data(),
                              vec.size(),
                              &bytes_read) && bytes_read > 0) {
            return bytes_read;
        }
        error_code = GetLastError();
        return 0;
    }

    // avoid read too big file
    std::string http::read_string_to_end(const std::wstring &input_url) {
        do {
            http client(input_url);
            unsigned long content_length = 0;
            if (!client.url_crack()) {
                break;
            }
            if (!client.open()) {
                break;
            }
            if (!client.connect()) {
                break;
            }
            if (!client.open_request()) {
                break;
            }
            if (!client.send_request()) {
                break;
            }

            content_length = client.get_content_length();
            if (content_length <= 0 ||
                content_length >= 5 * 1024 * 1024) {
                break;
            }

            std::string body(content_length, '\0');
            unsigned long bytes_read = 0;
            if (!client.read(body.data(),
                             content_length,
                             &bytes_read)) {
                break;
            }
            body.shrink_to_fit();
            return body;
        } while (false);
        return {};
    }

    std::wstring http::read_wstring_to_end(const std::wstring &input_url) {
        return helper::convert::str_to_wstr(read_string_to_end(input_url));
    }

    std::vector<uint8_t> http::read_bytes_to_end(
        const std::wstring &input_url) {
        do {
            http client(input_url);
            unsigned long content_length = 0;
            if (!client.url_crack()) {
                break;
            }
            if (!client.open()) {
                break;
            }
            if (!client.connect()) {
                break;
            }
            if (!client.open_request()) {
                break;
            }
            if (!client.send_request()) {
                break;
            }
            content_length = client.get_content_length();
            if (content_length <= 0 || content_length >= 5 * 1024 * 1024) {
                break;
            }

            std::vector<uint8_t> body(content_length, '\0');
            unsigned long bytes_read = 0;
            if (!client.read(body.data(),
                             content_length,
                             &bytes_read)) {
                break;
            }
            body.shrink_to_fit();
            return body;
        } while (false);
        return {};
    }

    // support http and https
    unsigned long http::download(const std::wstring &input_url,
                                 const wchar_t *file_name) {
        unsigned long error = 0;
        http client(input_url);
        unsigned long content_length = 0;
        fs file;
        HANDLE file_handle = file.create(file_name);
        if (!file_handle) {
            return file.err_code();
        }
        do {
            if (!client.url_crack()) {
                break;
            }
            if (!client.open()) {
                break;
            }
            if (!client.connect()) {
                break;
            }
            if (!client.open_request()) {
                break;
            }
            if (!client.send_request()) {
                break;
            }
            content_length = client.get_content_length();
            if (content_length <= 0) {
                break;
            }

            unsigned long buf_size = 4096;
            uint8_t *buf = new uint8_t[buf_size];
            memset(buf, 0, buf_size);
            unsigned long bytes_read = 0;
            unsigned long bytes_written = 0;
            do {
                if (!client.read(buf, buf_size, &bytes_read)) {
                    error = client.err_code();
                    break;
                }
                if (bytes_read <= 0) break;
                if (!file.write(file_handle,
                                buf,
                                bytes_read,
                                &bytes_written)) {
                    error = file.err_code();
                    break;
                }
            } while (bytes_read > 0 && bytes_written > 0);
            delete[] buf;
            return error;
        } while (false);
        return client.err_code();
    }

    // support http and https
    unsigned long http::upload(const std::wstring &input_url,
                               const wchar_t *file_name) {
        unsigned long error = 0;
        http client(input_url);
        fs file;
        HANDLE file_handle = file.open(file_name);
        if (!file_handle) {
            return file.err_code();
        }
        do {
            if (!client.url_crack()) {
                break;
            }
            if (!client.open(L"MiniUpload/0.1")) {
                break;
            }
            if (!client.connect()) {
                break;
            }
            if (!client.open_request(L"POST")) {
                break;
            }
            if (!client.add_header(
                L"Content-Type: application/octet-stream; charset=utf-8")) {
                break;
            }

            INTERNET_BUFFERSW buffers_in = {};
            buffers_in.dwStructSize = sizeof(INTERNET_BUFFERSW);
            buffers_in.dwBufferTotal = file.size(file_handle);
            if (!client.send_request_ex(&buffers_in,
                                        nullptr,
                                        0,
                                        0)) {
                break;
            }

            unsigned long buf_size = 4096;
            uint8_t *buf = new uint8_t[buf_size];
            memset(buf, 0, buf_size);
            unsigned long bytes_read = 0;
            unsigned long bytes_written = 0;
            do {
                if (!file.read(file_handle,
                               buf,
                               bytes_read,
                               &bytes_read)) {
                    error = file.err_code();
                    break;
                }
                if (bytes_read <= 0) break;
                if (!client.write(buf, bytes_read, &bytes_written)) {
                    error = client.err_code();
                    break;
                }
            } while (bytes_read > 0 && bytes_written > 0);
            delete[] buf;
            if (!client.end_request_ex()) {
                break;
            }
            return error;
        } while (false);
        return client.err_code();
    }


    unsigned long http::err_code() const {
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
}
