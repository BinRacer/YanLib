//
// Created by forkernel on 2025/4/5.
//

#include "http.h"
#include "helper/convert.h"
#include "fs.h"

namespace YanLib::io {
http::http(const std::string &input_url) {
    uc.dwStructSize      = sizeof(uc);
    uc.dwSchemeLength    = _countof(scheme) - 1;
    uc.dwHostNameLength  = _countof(hostname) - 1;
    uc.dwUserNameLength  = _countof(username) - 1;
    uc.dwPasswordLength  = _countof(password) - 1;
    uc.dwUrlPathLength   = _countof(urlpath) - 1;
    uc.dwExtraInfoLength = _countof(extra_info) - 1;
    uc.lpszScheme        = scheme;
    uc.lpszHostName      = hostname;
    uc.lpszUserName      = username;
    uc.lpszPassword      = password;
    uc.lpszUrlPath       = urlpath;
    uc.lpszExtraInfo     = extra_info;
    url                  = helper::convert::str_to_wstr(input_url);
}

http::http(const std::wstring &input_url) {
    uc.dwStructSize      = sizeof(uc);
    uc.dwSchemeLength    = _countof(scheme) - 1;
    uc.dwHostNameLength  = _countof(hostname) - 1;
    uc.dwUserNameLength  = _countof(username) - 1;
    uc.dwPasswordLength  = _countof(password) - 1;
    uc.dwUrlPathLength   = _countof(urlpath) - 1;
    uc.dwExtraInfoLength = _countof(extra_info) - 1;
    uc.lpszScheme        = scheme;
    uc.lpszHostName      = hostname;
    uc.lpszUserName      = username;
    uc.lpszPassword      = password;
    uc.lpszUrlPath       = urlpath;
    uc.lpszExtraInfo     = extra_info;
    url                  = input_url;
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

bool http::url_crack(uint32_t flag) {
    if (!InternetCrackUrlW(url.data(), url.size(), flag, &uc)) {
        error_code = GetLastError();
        return false;
    }
    port     = uc.nPort;
    is_https = _wcsicmp(scheme, L"https") == 0;
    return true;
}

bool http::add_header(const char *headers, uint32_t headers_length) {
    if (!HttpAddRequestHeadersA(
            request_handle, headers, headers_length, HTTP_ADDREQ_FLAG_ADD)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool http::add_header(const wchar_t *headers, uint32_t headers_length) {
    if (!HttpAddRequestHeadersW(
            request_handle, headers, headers_length, HTTP_ADDREQ_FLAG_ADD)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool http::add_header(const std::string &headers) {
    if (!HttpAddRequestHeadersA(request_handle, headers.data(), headers.size(),
            HTTP_ADDREQ_FLAG_ADD)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool http::add_header(const std::wstring &headers) {
    if (!HttpAddRequestHeadersW(request_handle, headers.data(), headers.size(),
            HTTP_ADDREQ_FLAG_ADD)) {
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
        if (!HttpAddRequestHeadersA(request_handle, line.data(), line.size(),
                HTTP_ADDREQ_FLAG_ADD)) {
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
        if (!HttpAddRequestHeadersW(request_handle, line.data(), line.size(),
                HTTP_ADDREQ_FLAG_ADD)) {
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
        if (!HttpAddRequestHeadersA(request_handle, line.data(), line.size(),
                HTTP_ADDREQ_FLAG_ADD)) {
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
        if (!HttpAddRequestHeadersW(request_handle, line.data(), line.size(),
                HTTP_ADDREQ_FLAG_ADD)) {
            error_code = GetLastError();
            return false;
        }
    }
    return true;
}

bool http::get_headers(std::unordered_map<std::string, std::string> &headers) {
    uint32_t size = 0;
    // first call to fetch the buffer size
    HttpQueryInfoW(request_handle, HTTP_QUERY_RAW_HEADERS_CRLF, nullptr,
        reinterpret_cast<unsigned long *>(&size), nullptr);
    error_code = GetLastError();
    if (error_code != ERROR_INSUFFICIENT_BUFFER)
        return false;
    // allocate wide char buffer
    std::vector<wchar_t> buffer(size / sizeof(wchar_t) + 1);
    if (!HttpQueryInfoW(request_handle, HTTP_QUERY_RAW_HEADERS_CRLF,
            buffer.data(), reinterpret_cast<unsigned long *>(&size), nullptr)) {
        error_code = GetLastError();
        return false;
    }

    // convert to utf-8
    int32_t len = WideCharToMultiByte(
        CP_UTF8, 0, buffer.data(), -1, nullptr, 0, nullptr, nullptr);
    std::string utf8_str(len, 0);
    WideCharToMultiByte(
        CP_UTF8, 0, buffer.data(), -1, utf8_str.data(), len, nullptr, nullptr);

    headers.clear();
    // split lines by CRLF
    size_t pos = 0;
    while (pos < utf8_str.size()) {
        size_t end = utf8_str.find("\r\n", pos);
        if (end == std::string::npos)
            break;

        std::string line = utf8_str.substr(pos, end - pos);
        pos              = end + 2;

        size_t colon     = line.find(':');
        if (colon != std::string::npos) {
            std::string key   = line.substr(0, colon);
            std::string value = line.substr(colon + 1);

            // standard process: remove space and tolower
            key.erase(
                std::remove_if(key.begin(), key.end(), isspace), key.end());
            std::transform(key.begin(), key.end(), key.begin(), tolower);

            value.erase(0, value.find_first_not_of(" \t"));
            headers[key] = value;
        }
    }
    return true;
}

bool http::get_headers(
    std::unordered_map<std::wstring, std::wstring> &headers) {
    std::unordered_map<std::string, std::string> src_map;
    if (!get_headers(src_map))
        return false;
    headers.clear();
    for (const auto &pair : src_map) {
        std::wstring key   = helper::convert::str_to_wstr(pair.first);
        std::wstring value = helper::convert::str_to_wstr(pair.second);
        headers.emplace(std::move(key), std::move(value));
    }
    return true;
}

bool http::get_headers_vec(std::vector<std::string> &headers) {
    uint32_t size = 0;
    // first call to fetch the buffer size
    HttpQueryInfoW(request_handle, HTTP_QUERY_RAW_HEADERS_CRLF, nullptr,
        reinterpret_cast<unsigned long *>(&size), nullptr);
    error_code = GetLastError();
    if (error_code != ERROR_INSUFFICIENT_BUFFER)
        return false;

    // allocate wide char buffer
    std::vector<wchar_t> buffer(size / sizeof(wchar_t) + 1);
    if (!HttpQueryInfoW(request_handle, HTTP_QUERY_RAW_HEADERS_CRLF,
            buffer.data(), reinterpret_cast<unsigned long *>(&size), nullptr)) {
        error_code = GetLastError();
        return false;
    }

    // convert to utf-8
    int32_t len = WideCharToMultiByte(
        CP_UTF8, 0, buffer.data(), -1, nullptr, 0, nullptr, nullptr);
    std::string utf8_str(len, 0);
    WideCharToMultiByte(
        CP_UTF8, 0, buffer.data(), -1, utf8_str.data(), len, nullptr, nullptr);

    headers.clear();
    // split lines by CRLF
    size_t pos = 0;
    while (pos < utf8_str.size()) {
        size_t end = utf8_str.find("\r\n", pos);
        if (end == std::string::npos)
            break;

        std::string line = utf8_str.substr(pos, end - pos);
        pos              = end + 2;
        headers.push_back(line);
    }
    return true;
}

bool http::get_headers_vec(std::vector<std::wstring> &headers) {
    std::vector<std::string> src;
    if (!get_headers_vec(src)) {
        return false;
    }
    headers.clear();
    for (const auto &line : src) {
        headers.push_back(helper::convert::str_to_wstr(line));
    }
    return true;
}

bool http::query_option(uint32_t option,
    void                        *buffer,
    uint32_t                    *buffer_length) {
    if (!InternetQueryOptionW(request_handle, option, buffer,
            reinterpret_cast<unsigned long *>(buffer_length))) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool http::set_option(uint32_t option, void *buffer, uint32_t buffer_length) {
    if (!InternetSetOptionW(request_handle, option, buffer, buffer_length)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool http::open(const char *agent_name,
    uint32_t                access_type,
    const char             *proxy,
    const char             *proxy_bypass,
    uint32_t                flag) {
    internet_handle =
        InternetOpenA(agent_name, access_type, proxy, proxy_bypass, flag);
    if (!internet_handle) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool http::open(const wchar_t *agent_name,
    uint32_t                   access_type,
    const wchar_t             *proxy,
    const wchar_t             *proxy_bypass,
    uint32_t                   flag) {
    internet_handle =
        InternetOpenW(agent_name, access_type, proxy, proxy_bypass, flag);
    if (!internet_handle) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool http::connect(uint32_t service, uint32_t flag, DWORD_PTR context) {
    connect_handle = InternetConnectW(internet_handle, hostname, port,
        wcslen(username) == 0 ? nullptr : username,
        wcslen(password) == 0 ? nullptr : password, service, flag, context);
    if (!connect_handle) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool http::open_request(const char *verb,
    const char                     *version,
    const char                     *referrer,
    const char                    **accept_types,
    uint32_t                        flag,
    DWORD_PTR                       context) {
    if (wcslen(extra_info) > 0) {
        wcscat_s(urlpath, _countof(urlpath) - 1, extra_info);
    }
    std::string url = helper::convert::wstr_to_str(urlpath);
    if (is_https) {
        flag =
            flag | INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID;
    }
    request_handle = HttpOpenRequestA(connect_handle, verb, url.data(), version,
        referrer, accept_types, flag, context);
    if (!request_handle) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool http::open_request(const wchar_t *verb,
    const wchar_t                     *version,
    const wchar_t                     *referrer,
    const wchar_t                    **accept_types,
    uint32_t                           flag,
    DWORD_PTR                          context) {
    if (wcslen(extra_info) > 0) {
        wcscat_s(urlpath, _countof(urlpath) - 1, extra_info);
    }

    if (is_https) {
        flag =
            flag | INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID;
    }

    request_handle = HttpOpenRequestW(connect_handle, verb, urlpath, version,
        referrer, accept_types, flag, context);
    if (!request_handle) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

uint32_t http::get_content_length() {
    uint32_t content_length = 0;
    uint32_t buffer_size    = sizeof(content_length);
    uint32_t flags = HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER;

    if (!HttpQueryInfoW(request_handle, flags, &content_length,
            reinterpret_cast<unsigned long *>(&buffer_size), nullptr)) {
        error_code = GetLastError();
        return 0;
    }
    return content_length;
}

// support http and https
bool http::send_request(const char *headers,
    uint32_t                        headers_length,
    void                           *optional,
    uint32_t                        optional_length) {
    if (is_https) {
        do {
            uint32_t flags = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
                             SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
            if (!set_option(
                    INTERNET_OPTION_SECURITY_FLAGS, &flags, sizeof(flags))) {
                break;
            }
            if (!HttpSendRequestA(request_handle, headers, headers_length,
                    optional, optional_length)) {
                error_code = GetLastError();
                break;
            }
            return true;
        } while (false);
        return false;
    } else {
        if (!HttpSendRequestA(request_handle, headers, headers_length, optional,
                optional_length)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }
}

// support http and https
bool http::send_request(const wchar_t *headers,
    uint32_t                           headers_length,
    void                              *optional,
    uint32_t                           optional_length) {
    if (is_https) {
        do {
            uint32_t flags = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
                             SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
            if (!set_option(
                    INTERNET_OPTION_SECURITY_FLAGS, &flags, sizeof(flags))) {
                break;
            }
            if (!HttpSendRequestW(request_handle, headers, headers_length,
                    optional, optional_length)) {
                error_code = GetLastError();
                break;
            }
            return true;
        } while (false);
        return false;
    } else {
        if (!HttpSendRequestW(request_handle, headers, headers_length, optional,
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
    INTERNET_BUFFERSW                        *buffers_out,
    uint32_t                                  flag,
    DWORD_PTR                                 context) {
    if (is_https) {
        do {
            uint32_t flags = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
                             SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
            if (!set_option(
                    INTERNET_OPTION_SECURITY_FLAGS, &flags, sizeof(flags))) {
                break;
            }
            if (!HttpSendRequestExW(
                    request_handle, buffers_in, buffers_out, flag, context)) {
                error_code = GetLastError();
                break;
            }
            return true;
        } while (false);
        return false;
    } else {
        if (!HttpSendRequestExW(
                request_handle, buffers_in, buffers_out, flag, context)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }
}

// call send_request_ex(), next must call end_request_ex()
bool http::end_request_ex(INTERNET_BUFFERSW *buffers_out,
    uint32_t                                 flag,
    DWORD_PTR                                context) {
    if (!HttpEndRequestW(request_handle, buffers_out, flag, context)) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

bool http::read(void *buf, uint32_t size, uint32_t *ret_size) {
    if (!InternetReadFile(request_handle, buf, size,
            reinterpret_cast<unsigned long *>(ret_size))) {
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
    uint32_t             bytes_read = 0;
    if (InternetReadFile(request_handle, raw_data.data(), buffer_size,
            reinterpret_cast<unsigned long *>(&bytes_read)) &&
        bytes_read > 0) {
        raw_data.resize(bytes_read);
        raw_data.shrink_to_fit();
        return raw_data;
    }
    error_code = GetLastError();
    return {};
}

bool http::write(const void *buf, uint32_t size, uint32_t *ret_size) {
    if (!InternetWriteFile(request_handle, buf, size,
            reinterpret_cast<unsigned long *>(ret_size))) {
        error_code = GetLastError();
        return false;
    }
    return true;
}

uint32_t http::write_bytes(const std::vector<uint8_t> &vec) {
    uint32_t bytes_read = 0;
    if (InternetWriteFile(request_handle, vec.data(), vec.size(),
            reinterpret_cast<unsigned long *>(&bytes_read)) &&
        bytes_read > 0) {
        return bytes_read;
    }
    error_code = GetLastError();
    return 0;
}

// avoid read too big file
std::string http::read_string_to_end(const std::string &input_url) {
    do {
        http     client(input_url);
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
        uint32_t    bytes_read = 0;
        if (!client.read(body.data(), content_length, &bytes_read)) {
            break;
        }
        body.shrink_to_fit();
        return body;
    } while (false);
    return {};
}

// avoid read too big file
std::wstring http::read_wstring_to_end(const std::wstring &input_url) {
    do {
        http     client(input_url);
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
        uint32_t    bytes_read = 0;
        if (!client.read(body.data(), content_length, &bytes_read)) {
            break;
        }
        body.shrink_to_fit();
        return helper::convert::str_to_wstr(body);
    } while (false);
    return {};
}

std::vector<uint8_t> http::read_bytes_to_end(const std::string &input_url) {
    do {
        http     client(input_url);
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

        std::vector<uint8_t> body(content_length, '\0');
        uint32_t             bytes_read = 0;
        if (!client.read(body.data(), content_length, &bytes_read)) {
            break;
        }
        body.shrink_to_fit();
        return body;
    } while (false);
    return {};
}

std::vector<uint8_t> http::read_bytes_to_end(const std::wstring &input_url) {
    do {
        http     client(input_url);
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

        std::vector<uint8_t> body(content_length, '\0');
        uint32_t             bytes_read = 0;
        if (!client.read(body.data(), content_length, &bytes_read)) {
            break;
        }
        body.shrink_to_fit();
        return body;
    } while (false);
    return {};
}

// support http and https
uint32_t http::download(const std::string &input_url, const char *file_name) {
    uint32_t error = 0;
    http     client(input_url);
    uint32_t content_length = 0;
    fs       file(file_name, DesiredAccess::Read | DesiredAccess::Write,
              ShareMode::Read | ShareMode::Write, nullptr,
              CreationDisposition::CreateAlways);
    if (!file.is_ok()) {
        return file.err_code();
    }
    do {
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
        if (content_length <= 0) {
            break;
        }

        uint32_t             buf_size = 4096;
        std::vector<uint8_t> buf(buf_size, '\0');
        uint32_t             bytes_read    = 0;
        uint32_t             bytes_written = 0;
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
        return error;
    } while (false);
    return client.err_code();
}

// support http and https
uint32_t http::download(const std::wstring &input_url,
    const wchar_t                          *file_name) {
    uint32_t error = 0;
    http     client(input_url);
    uint32_t content_length = 0;
    fs       file(file_name, DesiredAccess::Read | DesiredAccess::Write,
              ShareMode::Read | ShareMode::Write, nullptr,
              CreationDisposition::CreateAlways);
    if (!file.is_ok()) {
        return file.err_code();
    }
    do {
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
        if (content_length <= 0) {
            break;
        }

        uint32_t             buf_size = 4096;
        std::vector<uint8_t> buf(buf_size, '\0');
        uint32_t             bytes_read    = 0;
        uint32_t             bytes_written = 0;
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
        return error;
    } while (false);
    return client.err_code();
}

// support http and https
uint32_t http::upload(const std::string &input_url, const char *file_name) {
    uint32_t error = 0;
    http     client(input_url);
    fs       file(file_name);
    if (!file.is_ok()) {
        return file.err_code();
    }
    do {
        if (!client.url_crack()) {
            break;
        }
        if (!client.open("MiniUpload/0.1")) {
            break;
        }
        if (!client.connect()) {
            break;
        }
        if (!client.open_request("POST")) {
            break;
        }
        if (!client.add_header(
                "Content-Type: application/octet-stream; charset=utf-8")) {
            break;
        }

        INTERNET_BUFFERSW buffers_in = {};
        buffers_in.dwStructSize      = sizeof(INTERNET_BUFFERSW);
        buffers_in.dwBufferTotal     = file.size();
        if (!client.send_request_ex(&buffers_in, nullptr, 0, 0)) {
            break;
        }

        uint32_t             buf_size = 4096;
        std::vector<uint8_t> buf(buf_size, '\0');
        uint32_t             bytes_read    = 0;
        uint32_t             bytes_written = 0;
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
            break;
        }
        return error;
    } while (false);
    return client.err_code();
}

// support http and https
uint32_t http::upload(const std::wstring &input_url, const wchar_t *file_name) {
    uint32_t error = 0;
    http     client(input_url);
    fs       file(file_name);
    if (!file.is_ok()) {
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
        buffers_in.dwStructSize      = sizeof(INTERNET_BUFFERSW);
        buffers_in.dwBufferTotal     = file.size();
        if (!client.send_request_ex(&buffers_in, nullptr, 0, 0)) {
            break;
        }

        uint32_t             buf_size = 4096;
        std::vector<uint8_t> buf(buf_size, '\0');
        uint32_t             bytes_read    = 0;
        uint32_t             bytes_written = 0;
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
            break;
        }
        return error;
    } while (false);
    return client.err_code();
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
