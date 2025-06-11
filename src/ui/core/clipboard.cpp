/* clang-format off */
/*
 * @file clipboard.cpp
 * @date 2025-04-30
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
#include "clipboard.h"
#include "helper/convert.h"

namespace YanLib::ui::core {
    clipboard::~clipboard() {
        if (is_create) {
            CloseClipboard();
        }
    }

    clipboard::clipboard(HWND window_handle) {
        if (!OpenClipboard(window_handle)) {
            error_code = GetLastError();
            is_create = false;
        } else {
            is_create = true;
        }
    }

    bool clipboard::is_ok() const {
        return is_create;
    }

    uint32_t clipboard::register_format(const char *format) {
        const uint32_t result = RegisterClipboardFormatA(format);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t clipboard::register_format(const wchar_t *format) {
        const uint32_t result = RegisterClipboardFormatW(format);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    bool clipboard::clear() {
        if (!EmptyClipboard()) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    std::vector<uint8_t> clipboard::get_data(uint32_t format) {
        HANDLE mem_handle = nullptr;
        std::vector<uint8_t> data = {};
        do {
            mem_handle = GetClipboardData(format);
            if (!mem_handle) {
                error_code = GetLastError();
                break;
            }
            const void *addr = GlobalLock(mem_handle);
            if (!addr) {
                error_code = GetLastError();
                break;
            }
            do {
                const size_t size = GlobalSize(mem_handle);
                if (!size) {
                    error_code = GetLastError();
                    break;
                }
                data.resize(size);
                memcpy_s(data.data(), size, addr, size);
            } while (false);
            if (!GlobalUnlock(mem_handle)) {
                error_code = GetLastError();
            }
        } while (false);
        return data;
    }

    bool clipboard::set_data(const std::vector<uint8_t> &data,
                             uint32_t format) {
        HGLOBAL mem_handle = nullptr;
        bool result = false;
        do {
            mem_handle =
                    GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, data.size() + 2);
            if (!mem_handle) {
                error_code = GetLastError();
                break;
            }
            void *addr = GlobalLock(mem_handle);
            if (!addr) {
                error_code = GetLastError();
                break;
            }
            memcpy_s(addr, data.size(), data.data(), data.size());
            if (!GlobalUnlock(mem_handle)) {
                error_code = GetLastError();
                break;
            }
            if (!SetClipboardData(format, mem_handle)) {
                error_code = GetLastError();
                break;
            }
            result = true;
        } while (false);
        if (mem_handle && !GlobalFree(mem_handle)) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t clipboard::get_format_name(uint32_t format,
                                       std::string &format_name) {
        const int32_t result =
                GetClipboardFormatNameA(format, format_name.data(),
                                        static_cast<int32_t>(
                                                format_name.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t clipboard::get_format_name(uint32_t format,
                                       std::wstring &format_name) {
        const int32_t result =
                GetClipboardFormatNameW(format, format_name.data(),
                                        static_cast<int32_t>(
                                                format_name.size()));
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    HWND clipboard::get_open_window() {
        HWND window_handle = GetOpenClipboardWindow();
        if (!window_handle) {
            error_code = GetLastError();
        }
        return window_handle;
    }

    HWND clipboard::get_owner_window() {
        HWND result = GetClipboardOwner();
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t clipboard::get_sequence_number() {
        return GetClipboardSequenceNumber();
    }

    HWND clipboard::get_viewer_window() {
        HWND result = GetClipboardViewer();
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t clipboard::get_priority_format(
            std::vector<uint32_t> &format_priority_list) {
        const int32_t result = GetPriorityClipboardFormat(
                format_priority_list.data(),
                static_cast<int32_t>(format_priority_list.size()));
        if (result == -1) {
            error_code = GetLastError();
        }
        return result;
    }

    bool clipboard::get_updated_formats(std::vector<uint32_t> &formats,
                                        uint32_t *real_size) {
        if (!GetUpdatedClipboardFormats(formats.data(), formats.size(),
                                        real_size)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool clipboard::is_format_available(uint32_t format) {
        if (!IsClipboardFormatAvailable(format)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool clipboard::add_format_listener(HWND window_handle) {
        if (!AddClipboardFormatListener(window_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool clipboard::remove_format_listener(HWND window_handle) {
        if (!RemoveClipboardFormatListener(window_handle)) {
            error_code = GetLastError();
            return false;
        }
        return true;
    }

    bool clipboard::change_chain(HWND remove_window_handle,
                                 HWND next_window_handle) {
        return ChangeClipboardChain(remove_window_handle, next_window_handle);
    }

    uint32_t clipboard::enum_formats(uint32_t format) {
        const uint32_t result = EnumClipboardFormats(format);
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    int32_t clipboard::count_formats() {
        const int32_t result = CountClipboardFormats();
        if (!result) {
            error_code = GetLastError();
        }
        return result;
    }

    uint32_t clipboard::err_code() const {
        return error_code;
    }

    std::string clipboard::err_string() const {
        std::string result = helper::convert::err_string(error_code);
        return result;
    }

    std::wstring clipboard::err_wstring() const {
        std::wstring result = helper::convert::err_wstring(error_code);
        return result;
    }
} // namespace YanLib::ui::core
