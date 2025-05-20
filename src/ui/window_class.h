//
// Created by forkernel on 2025/5/18.
//

#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H
#include <Windows.h>
#include <string>

namespace YanLib::ui {
#ifndef CLASSSTYLE
#define CLASSSTYLE

    enum class ClassStyle : uint32_t {
        VRedraw = CS_VREDRAW,
        HRedraw = CS_HREDRAW,
        DoubleClick = CS_DBLCLKS,
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
} // namespace YanLib::ui
#endif // WINDOW_CLASS_H
