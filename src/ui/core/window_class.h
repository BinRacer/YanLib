/* clang-format off */
/*
 * @file window_class.h
 * @date 2025-05-18
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
#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H
#include <Windows.h>
#include <string>

namespace YanLib::ui::core {
#ifndef CLASSSTYLE
#define CLASSSTYLE

    enum class ClassStyle : uint32_t {
        VRedraw = CS_VREDRAW,
        HRedraw = CS_HREDRAW,
        DoubleClicks = CS_DBLCLKS,
        OwnDC = CS_OWNDC,
        ClassDC = CS_CLASSDC,
        ParentDC = CS_PARENTDC,
        NoClose = CS_NOCLOSE,
        SaveBits = CS_SAVEBITS,
        ByteAlignClient = CS_BYTEALIGNCLIENT,
        ByteAlignWindow = CS_BYTEALIGNWINDOW,
        GlobalClass = CS_GLOBALCLASS,
        Ime = CS_IME,
        DropShadow = CS_DROPSHADOW,
    };

    inline ClassStyle operator|(ClassStyle a, ClassStyle b) {
        return static_cast<ClassStyle>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
#endif

    class window_class {
    private:
        uint32_t error_code = 0;

    public:
        window_class(const window_class &other) = delete;

        window_class(window_class &&other) = delete;

        window_class &operator=(const window_class &other) = delete;

        window_class &operator=(window_class &&other) = delete;

        window_class() = default;

        ~window_class() = default;

        WNDCLASSEXA
        make(const char *class_name,
             WNDPROC window_proc,
             HINSTANCE instance_handle,
             ClassStyle style = ClassStyle::HRedraw | ClassStyle::VRedraw,
             const char *menu_name = nullptr,
             int32_t class_extra_size = 0,
             int32_t window_extra_size = 0,
             HICON icon_handle = LoadIconW(nullptr, IDI_APPLICATION),
             HCURSOR cursor_handle = LoadCursorW(nullptr, IDC_ARROW),
             HBRUSH brush_background_handle =
                     static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)),
             HICON icon_small_handle = nullptr);

        WNDCLASSEXW
        make(const wchar_t *class_name,
             WNDPROC window_proc,
             HINSTANCE instance_handle,
             ClassStyle style = ClassStyle::HRedraw | ClassStyle::VRedraw,
             const wchar_t *menu_name = nullptr,
             int32_t class_extra_size = 0,
             int32_t window_extra_size = 0,
             HICON icon_handle = LoadIconW(nullptr, IDI_APPLICATION),
             HCURSOR cursor_handle = LoadCursorW(nullptr, IDC_ARROW),
             HBRUSH brush_background_handle =
                     static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)),
             HICON icon_small_handle = nullptr);

        ATOM register_class(const WNDCLASSEXA *window_class);

        ATOM register_class(const WNDCLASSEXW *window_class);

        bool unregister_class(const char *class_name,
                              HINSTANCE instance_handle);

        bool unregister_class(const wchar_t *class_name,
                              HINSTANCE instance_handle);

        bool get_info(HINSTANCE instance_handle,
                      const char *class_name,
                      WNDCLASSA *window_class);

        bool get_info(HINSTANCE instance_handle,
                      const wchar_t *class_name,
                      WNDCLASSW *window_class);

        bool get_info(HINSTANCE instance_handle,
                      const char *class_name,
                      WNDCLASSEXA *window_class);

        bool get_info(HINSTANCE instance_handle,
                      const wchar_t *class_name,
                      WNDCLASSEXW *window_class);

        uint32_t get_long(HWND window_handle, int32_t index);

        uint32_t set_long(HWND window_handle, int32_t index, int32_t value);

        uintptr_t get_long_ptr(HWND window_handle, int32_t index);

        uintptr_t
        set_long_ptr(HWND window_handle, int32_t index, intptr_t value);

        uint16_t get_word(HWND window_handle, int32_t index);

        uint16_t set_word(HWND window_handle, int32_t index, uint16_t value);

        int32_t get_name(HWND window_handle, std::string &class_name);

        int32_t get_name(HWND window_handle, std::wstring &class_name);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };
} // namespace YanLib::ui::core
#endif // WINDOW_CLASS_H
