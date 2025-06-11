/* clang-format off */
/*
 * @file ftp.h
 * @date 2025-04-06
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
#ifndef FTP_H
#define FTP_H
#include <Windows.h>
#include <WinInet.h>
#include <string>
#include <vector>
#include "helper/convert.h"
#include "sync/rwlock.h"
#pragma comment(lib, "wininet.Lib")

namespace YanLib::io {
    class ftp {
    private:
        std::vector<HINTERNET> file_handles = {};
        sync::rwlock rwlock = {};
        HINTERNET internet_handle = nullptr;
        HINTERNET session_read_handle = nullptr;
        HINTERNET session_upload_handle = nullptr;
        std::wstring url = {};
        URL_COMPONENTSW uc = {};
        wchar_t scheme[16] = {};
        wchar_t _hostname[128] = {};
        wchar_t _username[32] = {};
        wchar_t _password[32] = {};
        wchar_t urlpath[512] = {};
        wchar_t extra_info[256] = {};
        uint16_t _port = 0;
        uint32_t error_code = 0;

    public:
        ftp(const ftp &other) = delete;

        ftp(ftp &&other) = delete;

        ftp &operator=(const ftp &other) = delete;

        ftp &operator=(ftp &&other) = delete;

        ftp() = delete;

        explicit ftp(const std::string &input_url,
                     helper::CodePage code_page = helper::curr_code_page());

        explicit ftp(const std::wstring &input_url);

        explicit ftp(const std::string &ip,
                     const uint16_t &port,
                     const std::string &username = {},
                     const std::string &password = {},
                     helper::CodePage code_page = helper::curr_code_page());

        explicit ftp(const std::wstring &ip,
                     const uint16_t &port,
                     const std::wstring &username = {},
                     const std::wstring &password = {});

        ~ftp();

        bool url_crack(uint32_t flag = ICU_DECODE | ICU_ESCAPE);

        bool open(const char *agent_name /* "MiniFTP/0.1" */,
                  uint32_t access_type = INTERNET_OPEN_TYPE_PRECONFIG,
                  const char *proxy = nullptr,
                  const char *proxy_bypass = nullptr,
                  uint32_t flag = 0);

        bool open(const wchar_t *agent_name /* L"MiniFTP/0.1" */,
                  uint32_t access_type = INTERNET_OPEN_TYPE_PRECONFIG,
                  const wchar_t *proxy = nullptr,
                  const wchar_t *proxy_bypass = nullptr,
                  uint32_t flag = 0);

        bool connect(uint32_t service = INTERNET_SERVICE_FTP,
                     uint32_t flag = INTERNET_FLAG_PASSIVE,
                     uintptr_t context = 0);

        HINTERNET open_file(const char *file_name,
                            uint32_t access = GENERIC_READ,
                            uint32_t flag = FTP_TRANSFER_TYPE_BINARY |
                                    INTERNET_FLAG_RELOAD |
                                    INTERNET_FLAG_TRANSFER_BINARY,
                            uintptr_t context = 0);

        HINTERNET open_file(const wchar_t *file_name,
                            uint32_t access = GENERIC_READ,
                            uint32_t flag = FTP_TRANSFER_TYPE_BINARY |
                                    INTERNET_FLAG_RELOAD |
                                    INTERNET_FLAG_TRANSFER_BINARY,
                            uintptr_t context = 0);

        HINTERNET create_file(const char *file_name,
                              uint32_t access = GENERIC_WRITE,
                              uint32_t flag = FTP_TRANSFER_TYPE_BINARY |
                                      INTERNET_FLAG_RELOAD |
                                      INTERNET_FLAG_TRANSFER_BINARY,
                              uintptr_t context = 0);

        HINTERNET create_file(const wchar_t *file_name,
                              uint32_t access = GENERIC_WRITE,
                              uint32_t flag = FTP_TRANSFER_TYPE_BINARY |
                                      INTERNET_FLAG_RELOAD |
                                      INTERNET_FLAG_TRANSFER_BINARY,
                              uintptr_t context = 0);

        bool read(HINTERNET file_handle,
                  void *buf,
                  uint32_t size,
                  uint32_t *ret_size);

        std::vector<uint8_t> read_bytes(HINTERNET file_handle,
                                        int32_t buffer_size = 1024);

        bool write(HINTERNET file_handle,
                   const void *buf,
                   uint32_t size,
                   uint32_t *ret_size);

        uint32_t write_bytes(HINTERNET file_handle,
                             const std::vector<uint8_t> &data);

        int64_t size(HINTERNET file_handle);

        bool pwd(std::string &path);

        bool pwd(std::wstring &path);

        bool cd(const char *dir);

        bool cd(const wchar_t *dir);

        bool ls(std::vector<std::string> &files,
                std::vector<std::string> &dirs);

        bool ls(std::vector<std::wstring> &files,
                std::vector<std::wstring> &dirs);

        bool ls_full_path(std::vector<std::string> &files,
                          std::vector<std::string> &dirs);

        bool ls_full_path(std::vector<std::wstring> &files,
                          std::vector<std::wstring> &dirs);

        bool mkdir(const char *dir);

        bool mkdir(const wchar_t *dir);

        bool rmdir(const char *dir);

        bool rmdir(const wchar_t *dir);

        bool rm(const char *file_name);

        bool rm(const wchar_t *file_name);

        bool rename(const char *existing_name, const char *new_name);

        bool rename(const wchar_t *existing_name, const wchar_t *new_name);

        std::vector<uint8_t> command(const char *command);

        std::vector<uint8_t> command(const wchar_t *command);

        bool download(const char *remote_file,
                      const char *new_file,
                      bool is_fail_if_exists = false,
                      uint32_t flags_and_attrs = FILE_ATTRIBUTE_NORMAL,
                      uint32_t flag = FTP_TRANSFER_TYPE_BINARY |
                              INTERNET_FLAG_RELOAD |
                              INTERNET_FLAG_TRANSFER_BINARY,
                      uintptr_t context = 0);

        bool download(const wchar_t *remote_file,
                      const wchar_t *new_file,
                      bool is_fail_if_exists = false,
                      uint32_t flags_and_attrs = FILE_ATTRIBUTE_NORMAL,
                      uint32_t flag = FTP_TRANSFER_TYPE_BINARY |
                              INTERNET_FLAG_RELOAD |
                              INTERNET_FLAG_TRANSFER_BINARY,
                      uintptr_t context = 0);

        bool upload(const char *local_file,
                    const char *new_remote_file,
                    uint32_t flag = FTP_TRANSFER_TYPE_BINARY |
                            INTERNET_FLAG_RELOAD |
                            INTERNET_FLAG_TRANSFER_BINARY,
                    uintptr_t context = 0);

        bool upload(const wchar_t *local_file,
                    const wchar_t *new_remote_file,
                    uint32_t flag = FTP_TRANSFER_TYPE_BINARY |
                            INTERNET_FLAG_RELOAD |
                            INTERNET_FLAG_TRANSFER_BINARY,
                    uintptr_t context = 0);

        uint32_t download2(HINTERNET remote_file, const char *local_file);

        uint32_t download2(HINTERNET remote_file, const wchar_t *local_file);

        uint32_t upload2(HINTERNET remote_file, const char *local_file);

        uint32_t upload2(HINTERNET remote_file, const wchar_t *local_file);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::io
#endif // FTP_H
