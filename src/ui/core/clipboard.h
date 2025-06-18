/* clang-format off */
/*
 * @file clipboard.h
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
#ifndef CLIPBOARD_H
#define CLIPBOARD_H
#include <Windows.h>
#include <WinUser.h>
#include <windef.h>
#include <string>
#include <vector>
namespace YanLib::ui::core {
    class clipboard {
    private:
        volatile bool is_create = false;
        uint32_t error_code = 0;

    public:
        clipboard(const clipboard &other) = delete;

        clipboard(clipboard &&other) = delete;

        clipboard &operator=(const clipboard &other) = delete;

        clipboard &operator=(clipboard &&other) = delete;

        clipboard() = delete;

        ~clipboard();

        explicit clipboard(HWND window_handle = nullptr);

        [[nodiscard]] bool is_ok() const;

        uint32_t register_format(const char *format);

        uint32_t register_format(const wchar_t *format);

        bool clear();

        std::vector<uint8_t> get_data(uint32_t format = CF_UNICODETEXT);

        bool set_data(const std::vector<uint8_t> &data,
                      uint32_t format = CF_UNICODETEXT);

        int32_t get_format_name(uint32_t format, std::string &format_name);

        int32_t get_format_name(uint32_t format, std::wstring &format_name);

        HWND get_open_window();

        HWND get_owner_window();

        uint32_t get_sequence_number();

        HWND get_viewer_window();

        int32_t
        get_priority_format(std::vector<uint32_t> &format_priority_list);

        bool get_updated_formats(std::vector<uint32_t> &formats,
                                 uint32_t *real_size);

        bool is_format_available(uint32_t format);

        bool add_format_listener(HWND window_handle);

        bool remove_format_listener(HWND window_handle);

        bool change_chain(HWND remove_window_handle, HWND next_window_handle);

        uint32_t enum_formats(uint32_t format);

        int32_t count_formats();

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // CLIPBOARD_H
