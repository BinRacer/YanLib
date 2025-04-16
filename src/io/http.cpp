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
        if (hRequest) {
            InternetCloseHandle(hRequest);
            hRequest = nullptr;
        }
        if (hConnect) {
            InternetCloseHandle(hConnect);
            hConnect = nullptr;
        }
        if (hInternet) {
            InternetCloseHandle(hInternet);
            hInternet = nullptr;
        }
    }

    bool http::url_crack(DWORD dwFlags) {
        if (!InternetCrackUrlW(
            url.data(),
            url.size(),
            dwFlags,
            &uc)) {
            error_code = GetLastError();
            return false;
        }
        port = uc.nPort;
        isHTTPS = _wcsicmp(scheme, L"https") == 0;
        return true;
    }

    bool http::add_header(const wchar_t *lpszHeaders,
                          DWORD dwHeadersLength) {
        if (!HttpAddRequestHeadersW(hRequest,
                                    lpszHeaders,
                                    dwHeadersLength,
                                    HTTP_ADDREQ_FLAG_ADD)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::add_header(std::string lpszHeaders) {
        std::wstring line = helper::convert::str_to_wstr(lpszHeaders);
        if (!HttpAddRequestHeadersW(hRequest,
                                    line.data(),
                                    line.size(),
                                    HTTP_ADDREQ_FLAG_ADD)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::add_header(std::wstring lpszHeaders) {
        if (!HttpAddRequestHeadersW(hRequest,
                                    lpszHeaders.data(),
                                    lpszHeaders.size(),
                                    HTTP_ADDREQ_FLAG_ADD)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::add_headers(std::unordered_map<std::string, std::string> &map) {
        if (map.size() == 0) {
            return false;
        }
        for (const auto &pair: map) {
            std::wstring key = helper::convert::str_to_wstr(pair.first);
            std::wstring value = helper::convert::str_to_wstr(pair.second);
            std::wstring line = key + L": " + value;
            if (!HttpAddRequestHeadersW(hRequest,
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
        if (map.size() == 0) {
            return false;
        }
        for (const auto &pair: map) {
            std::wstring key = pair.first;
            std::wstring value = pair.second;
            std::wstring line = key + L": " + value;
            if (!HttpAddRequestHeadersW(hRequest,
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
        if (vec.size() == 0) {
            return false;
        }
        for (const auto &ele: vec) {
            std::wstring line = helper::convert::str_to_wstr(ele);
            if (!HttpAddRequestHeadersW(hRequest,
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
        if (vec.size() == 0) {
            return false;
        }
        for (const auto &line: vec) {
            if (!HttpAddRequestHeadersW(hRequest,
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
        DWORD dwSize = 0;

        // first call to fetch the buffer size
        HttpQueryInfoW(hRequest,
                       HTTP_QUERY_RAW_HEADERS_CRLF,
                       nullptr,
                       &dwSize,
                       nullptr);
        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) return headers;

        // allocate wide char buffer
        std::vector<wchar_t> buffer(dwSize / sizeof(wchar_t) + 1);
        if (!HttpQueryInfoW(hRequest,
                            HTTP_QUERY_RAW_HEADERS_CRLF,
                            buffer.data(),
                            &dwSize,
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
        std::string utf8Str(len, 0);
        WideCharToMultiByte(CP_UTF8,
                            0,
                            buffer.data(),
                            -1,
                            utf8Str.data(),
                            len,
                            nullptr,
                            nullptr);

        // split lines by CRLF
        size_t pos = 0;
        while (pos < utf8Str.size()) {
            size_t end = utf8Str.find("\r\n", pos);
            if (end == std::string::npos) break;

            std::string line = utf8Str.substr(pos, end - pos);
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
        std::unordered_map<std::string, std::string> srcMap = get_headers();
        if (srcMap.size() == 0) {
            return {};
        }
        std::unordered_map<std::wstring, std::wstring> dstMap;
        for (const auto &pair: srcMap) {
            std::wstring key = helper::convert::str_to_wstr(pair.first);
            std::wstring value = helper::convert::str_to_wstr(pair.second);
            dstMap.emplace(std::move(key), std::move(value));
        }
        return dstMap;
    }

    std::vector<std::string> http::get_headers_vec() const {
        std::vector<std::string> headers;
        DWORD dwSize = 0;

        // first call to fetch the buffer size
        HttpQueryInfoW(hRequest,
                       HTTP_QUERY_RAW_HEADERS_CRLF,
                       nullptr,
                       &dwSize,
                       nullptr);
        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) return headers;

        // allocate wide char buffer
        std::vector<wchar_t> buffer(dwSize / sizeof(wchar_t) + 1);
        if (!HttpQueryInfoW(hRequest,
                            HTTP_QUERY_RAW_HEADERS_CRLF,
                            buffer.data(),
                            &dwSize,
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
        std::string utf8Str(len, 0);
        WideCharToMultiByte(CP_UTF8,
                            0,
                            buffer.data(),
                            -1,
                            utf8Str.data(),
                            len,
                            nullptr,
                            nullptr);

        // split lines by CRLF
        size_t pos = 0;
        while (pos < utf8Str.size()) {
            size_t end = utf8Str.find("\r\n", pos);
            if (end == std::string::npos) break;

            std::string line = utf8Str.substr(pos, end - pos);
            pos = end + 2;
            headers.push_back(line);
        }
        return headers;
    }

    std::vector<std::wstring> http::get_headers_vec_wide() const {
        std::vector<std::string> src = get_headers_vec();
        if (src.size() == 0) {
            return {};
        }
        std::vector<std::wstring> dst;
        for (const auto &line: src) {
            dst.push_back(helper::convert::str_to_wstr(line));
        }
        return dst;
    }

    bool http::query_option(DWORD dwOption,
                            LPVOID lpBuffer,
                            LPDWORD lpdwBufferLength) {
        if (!InternetQueryOptionW(hRequest,
                                  dwOption,
                                  lpBuffer,
                                  lpdwBufferLength)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::set_option(DWORD dwOption,
                          LPVOID lpBuffer,
                          DWORD dwBufferLength) {
        if (!InternetSetOptionW(hRequest, dwOption, lpBuffer, dwBufferLength)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::open(const wchar_t *lpszAgent,
                    DWORD dwAccessType,
                    const wchar_t *lpszProxy,
                    const wchar_t *lpszProxyBypass,
                    DWORD dwFlags) {
        hInternet = InternetOpenW(lpszAgent,
                                  dwAccessType,
                                  lpszProxy,
                                  lpszProxyBypass,
                                  dwFlags);
        if (!hInternet) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::connect(DWORD dwService,
                       DWORD dwFlags,
                       DWORD_PTR dwContext) {
        hConnect = InternetConnectW(hInternet,
                                    hostname,
                                    port,
                                    wcslen(username) == 0 ? nullptr : username,
                                    wcslen(password) == 0 ? nullptr : password,
                                    dwService,
                                    dwFlags,
                                    dwContext);
        if (!hConnect) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::open_request(const wchar_t *lpszVerb,
                            const wchar_t *lpszVersion,
                            const wchar_t *lpszReferrer,
                            const wchar_t **lplpszAcceptTypes,
                            DWORD dwFlags,
                            DWORD_PTR dwContext) {
        if (wcslen(extra_info) > 0) {
            wcscat_s(urlpath, _countof(urlpath) - 1, extra_info);
        }

        if (isHTTPS) {
            dwFlags = dwFlags |
                      INTERNET_FLAG_SECURE |
                      INTERNET_FLAG_IGNORE_CERT_CN_INVALID;
        }

        hRequest = HttpOpenRequestW(hConnect,
                                    lpszVerb,
                                    urlpath,
                                    lpszVersion,
                                    lpszReferrer,
                                    lplpszAcceptTypes,
                                    dwFlags,
                                    dwContext);
        if (!hRequest) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DWORD http::get_content_length() {
        DWORD contentLength = 0;
        DWORD bufferSize = sizeof(contentLength);
        DWORD dwFlags = HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER;

        if (!HttpQueryInfoW(hRequest,
                            dwFlags,
                            &contentLength,
                            &bufferSize,
                            nullptr)) {
            error_code = GetLastError();
            return 0;
        }
        return contentLength;
    }

    // support http and https
    bool http::send_request(const wchar_t *lpszHeaders,
                            DWORD dwHeadersLength,
                            LPVOID lpOptional,
                            DWORD dwOptionalLength) {
        if (isHTTPS) {
            do {
                DWORD dwFlags = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
                                SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
                if (!set_option(INTERNET_OPTION_SECURITY_FLAGS,
                                &dwFlags,
                                sizeof(dwFlags))) {
                    break;
                }
                if (!HttpSendRequestW(hRequest,
                                      lpszHeaders,
                                      dwHeadersLength,
                                      lpOptional,
                                      dwOptionalLength)) {
                    error_code = GetLastError();
                    break;
                }
                return true;
            } while (false);
            return false;
        } else {
            if (!HttpSendRequestW(hRequest,
                                  lpszHeaders,
                                  dwHeadersLength,
                                  lpOptional,
                                  dwOptionalLength)) {
                error_code = GetLastError();
                return false;
            }
            return true;
        }
    }

    // support http and https
    // call send_request_ex(), next must call end_request_ex()
    bool http::send_request_ex(LPINTERNET_BUFFERSW lpBuffersIn,
                               LPINTERNET_BUFFERSW lpBuffersOut,
                               DWORD dwFlags,
                               DWORD_PTR dwContext) {
        if (isHTTPS) {
            do {
                DWORD flag = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
                             SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
                if (!set_option(INTERNET_OPTION_SECURITY_FLAGS,
                                &flag,
                                sizeof(flag))) {
                    break;
                }
                if (!HttpSendRequestExW(hRequest,
                                        lpBuffersIn,
                                        lpBuffersOut,
                                        dwFlags,
                                        dwContext)) {
                    error_code = GetLastError();
                    break;
                }
                return true;
            } while (false);
            return false;
        } else {
            if (!HttpSendRequestExW(hRequest,
                                    lpBuffersIn,
                                    lpBuffersOut,
                                    dwFlags,
                                    dwContext)) {
                error_code = GetLastError();
                return false;
            }
            return true;
        }
    }

    // call send_request_ex(), next must call end_request_ex()
    bool http::end_request_ex(LPINTERNET_BUFFERSW lpBuffersOut,
                              DWORD dwFlags,
                              DWORD_PTR dwContext) {
        if (!HttpEndRequestW(hRequest, lpBuffersOut, dwFlags, dwContext)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool http::read(LPVOID lpBuffer,
                    DWORD dwNumberOfBytesToRead,
                    LPDWORD lpdwNumberOfBytesRead) {
        if (!InternetReadFile(hRequest,
                              lpBuffer,
                              dwNumberOfBytesToRead,
                              lpdwNumberOfBytesRead)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    std::vector<uint8_t> http::read_bytes(int32_t bufferSize) {
        if (bufferSize < 1024) {
            bufferSize = 1024;
        }
        std::vector<uint8_t> rawData(bufferSize, '\0');
        DWORD bytesRead = 0;
        if (InternetReadFile(hRequest,
                             rawData.data(),
                             bufferSize,
                             &bytesRead) && bytesRead > 0) {
            rawData.resize(bytesRead);
            rawData.shrink_to_fit();
            return rawData;
        }
        error_code = GetLastError();
        return {};
    }

    bool http::write(LPCVOID lpBuffer,
                     DWORD dwNumberOfBytesToWrite,
                     LPDWORD lpdwNumberOfBytesWritten) {
        if (!InternetWriteFile(hRequest,
                               lpBuffer,
                               dwNumberOfBytesToWrite,
                               lpdwNumberOfBytesWritten)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    DWORD http::write_bytes(std::vector<uint8_t> &vec) {
        DWORD bytesRead = 0;
        if (InternetWriteFile(hRequest,
                              vec.data(),
                              vec.size(),
                              &bytesRead) && bytesRead > 0) {
            return bytesRead;
        }
        error_code = GetLastError();
        return 0;
    }

    // avoid read too big file
    std::string http::read_string_to_end(const std::wstring &input_url) {
        do {
            http client(input_url);
            DWORD contentLength = 0;
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

            contentLength = client.get_content_length();
            if (contentLength <= 0 || contentLength >= 5 * 1024 * 1024) {
                break;
            }

            std::string body(contentLength, '\0');
            DWORD dwRead = 0;
            if (!client.read(body.data(), contentLength, &dwRead)) {
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
            DWORD contentLength = 0;
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
            contentLength = client.get_content_length();
            if (contentLength <= 0 || contentLength >= 5 * 1024 * 1024) {
                break;
            }

            std::vector<uint8_t> body(contentLength, '\0');
            DWORD dwRead = 0;
            if (!client.read(body.data(), contentLength, &dwRead)) {
                break;
            }
            body.shrink_to_fit();
            return body;
        } while (false);
        return {};
    }

    // support http and https
    DWORD http::download(const std::wstring &input_url,
                         const wchar_t *file_name) {
        DWORD dwError = 0;
        http client(input_url);
        DWORD contentLength = 0;
        fs file;
        if (!file.create(file_name)) {
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
            contentLength = client.get_content_length();
            if (contentLength <= 0) {
                break;
            }

            DWORD bufSize = 4096;
            uint8_t *buf = new uint8_t[bufSize];
            memset(buf, 0, bufSize);
            DWORD dwRead = 0;
            DWORD dwWritten = 0;
            do {
                if (!client.read(buf, bufSize, &dwRead)) {
                    dwError = client.err_code();
                    break;
                }
                if (dwRead <= 0) break;
                if (!file.write(buf, dwRead, &dwWritten)) {
                    dwError = file.err_code();
                    break;
                }
            } while (dwRead > 0 && dwWritten > 0);
            delete[] buf;
            return dwError;
        } while (false);
        return client.err_code();
    }

    // support http and https
    DWORD http::upload(const std::wstring &input_url,
                       const wchar_t *file_name) {
        DWORD dwError = 0;
        http client(input_url);
        fs file;
        if (!file.open(file_name)) {
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

            INTERNET_BUFFERSW buffersIn = {};
            buffersIn.dwStructSize = sizeof(INTERNET_BUFFERSW);
            buffersIn.dwBufferTotal = file.size();
            if (!client.send_request_ex(&buffersIn, nullptr, 0, 0)) {
                break;
            }

            DWORD bufSize = 4096;
            uint8_t *buf = new uint8_t[bufSize];
            memset(buf, 0, bufSize);
            DWORD dwRead = 0;
            DWORD dwWritten = 0;
            do {
                if (!file.read(buf, dwRead, &dwRead)) {
                    dwError = file.err_code();
                    break;
                }
                if (dwRead <= 0) break;
                if (!client.write(buf, dwRead, &dwWritten)) {
                    dwError = client.err_code();
                    break;
                }
            } while (dwRead > 0 && dwWritten > 0);
            delete[] buf;
            if (!client.end_request_ex()) {
                break;
            }
            return dwError;
        } while (false);
        return client.err_code();
    }


    DWORD http::err_code() const {
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
