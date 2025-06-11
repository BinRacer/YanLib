/* clang-format off */
/*
 * @file convert.cpp
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
#include "convert.h"

namespace YanLib::helper {
    std::wstring convert::str_to_wstr(const std::string &str,
                                      CodePage code_page) {
        const int32_t len =
                MultiByteToWideChar(static_cast<uint32_t>(code_page), 0,
                                    str.data(), -1, nullptr, 0);
        if (len <= 0)
            return {};
        std::wstring wstr(len, 0);
        MultiByteToWideChar(static_cast<uint32_t>(code_page), 0, str.data(), -1,
                            &wstr[0], len);
        wstr.resize(len - 1);
        wstr.shrink_to_fit();
        return wstr;
    }

    std::string convert::wstr_to_str(const std::wstring &wstr,
                                     CodePage code_page) {
        const int32_t len =
                WideCharToMultiByte(static_cast<uint32_t>(code_page), 0,
                                    wstr.data(), -1, nullptr, 0, nullptr,
                                    nullptr);
        if (len <= 0)
            return {};
        std::string str(len, 0);
        WideCharToMultiByte(static_cast<uint32_t>(code_page), 0, wstr.data(),
                            -1, &str[0], len, nullptr, nullptr);
        str.resize(len - 1);
        str.shrink_to_fit();
        return str;
    }

    std::string convert::err_string(const uint32_t error_code) {
        std::string result;
        HLOCAL hlocal = nullptr;
        constexpr uint32_t system_locale =
                MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);
        uint32_t is_ok =
                FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM |
                                       FORMAT_MESSAGE_IGNORE_INSERTS |
                                       FORMAT_MESSAGE_ALLOCATE_BUFFER,
                               nullptr, error_code, system_locale,
                               reinterpret_cast<char *>(&hlocal), 0, nullptr);
        if (!is_ok) {
            // Is it a network-related error?
            const HMODULE module_handle =
                    LoadLibraryExA("netmsg.dll", nullptr,
                                   DONT_RESOLVE_DLL_REFERENCES);

            if (module_handle != nullptr) {
                is_ok = FormatMessageA(FORMAT_MESSAGE_FROM_HMODULE |
                                               FORMAT_MESSAGE_IGNORE_INSERTS |
                                               FORMAT_MESSAGE_ALLOCATE_BUFFER,
                                       module_handle, error_code, system_locale,
                                       reinterpret_cast<char *>(&hlocal), 0,
                                       nullptr);
                FreeLibrary(module_handle);
            }
        }

        if (is_ok && (hlocal != nullptr)) {
            result = static_cast<char *>(LocalLock(hlocal));
            LocalFree(hlocal);
        }
        return result;
    }

    std::wstring convert::err_wstring(const uint32_t error_code) {
        std::wstring result;
        HLOCAL hlocal = nullptr;
        constexpr uint32_t system_locale =
                MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);
        uint32_t is_ok = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM |
                                                FORMAT_MESSAGE_IGNORE_INSERTS |
                                                FORMAT_MESSAGE_ALLOCATE_BUFFER,
                                        nullptr, error_code, system_locale,
                                        reinterpret_cast<wchar_t *>(&hlocal), 0,
                                        nullptr);
        if (!is_ok) {
            // Is it a network-related error?
            const HMODULE module_handle =
                    LoadLibraryExW(L"netmsg.dll", nullptr,
                                   DONT_RESOLVE_DLL_REFERENCES);

            if (module_handle != nullptr) {
                is_ok = FormatMessageW(FORMAT_MESSAGE_FROM_HMODULE |
                                               FORMAT_MESSAGE_IGNORE_INSERTS |
                                               FORMAT_MESSAGE_ALLOCATE_BUFFER,
                                       module_handle, error_code, system_locale,
                                       reinterpret_cast<wchar_t *>(&hlocal), 0,
                                       nullptr);
                FreeLibrary(module_handle);
            }
        }

        if (is_ok && (hlocal != nullptr)) {
            result = static_cast<wchar_t *>(LocalLock(hlocal));
            LocalFree(hlocal);
        }
        return result;
    }
} // namespace YanLib::helper
